#include <assert.h>
#include <chrono>
#include <utility>

#include "common/configmanager/configmanager.h"
#include "log/clog.h"
#include "simhub.h"

using namespace std::chrono_literals;

// TODO: FIX EVERYTHING

std::shared_ptr<SimHubEventController> SimHubEventController::_EventControllerInstance = NULL;

//! static singleton accessor
std::shared_ptr<SimHubEventController> SimHubEventController::EventControllerInstance(void)
{
    if (!_EventControllerInstance) {
        _EventControllerInstance.reset(new SimHubEventController());
    }

    return SimHubEventController::_EventControllerInstance;
}

//! allows reset of global singleton
void SimHubEventController::DestroyEventControllerInstance(void)
{
    logger.log(LOG_INFO, "Destroying event controller singleton");

    SimHubEventController::_EventControllerInstance.reset();
    SimHubEventController::_EventControllerInstance = NULL;
}

SimHubEventController::SimHubEventController()
{
    _prepare3dMethods.plugin_instance = NULL;
    _pokeyMethods.plugin_instance = NULL;
    _configManager = NULL;
    _running = false;

#if defined(_AWS_SDK)
    _awsHelper.init();
#endif

    logger.log(LOG_INFO, "Starting event controller");
}

//! like strtok but not evil
void split(const std::string &sequence, std::string &delims, std::vector<std::string> &tokens)
{
    size_t i = 0;
    size_t pos = sequence.find(delims);

    if (pos == std::string::npos){
        tokens.push_back(sequence);
        return;
    }

    while (pos != std::string::npos) {
        tokens.push_back(sequence.substr(i, pos-i));
        i = ++pos;
        pos = sequence.find(delims, pos);
        
        if (pos == std::string::npos) {
            tokens.push_back(sequence.substr(i, sequence.length()));
        }
    }
}

/**
 * rudimentary converter from libconfig content to JSON content -
 * doesn't suppoert '#' comments outside of dictionaries (like in
 * lists)
 */
std::string libconfigToJSON(std::string configFilename)
{
    std::ifstream file(configFilename);

    if (!file) {
        return "";
    }
    
    size_t lineIdx = 0;
    
    std::string line;
    std::stringstream jsonStream;

    std::string commentToken("#");
    std::string jsonAssign(":");
    
    jsonStream << "{" << std::endl;

    while (std::getline(file, line)) {
        lineIdx++;

        std::replace(line.begin(), line.end(), '=', ':');
        std::replace(line.begin(), line.end(), '(', '[');
        std::replace(line.begin(), line.end(), ')', ']');
        std::replace(line.begin(), line.end(), ';', ',');

        std::vector<std::string> tokens;

        split(line, commentToken, tokens);

        if (line.find(commentToken) != std::string::npos) {
            jsonStream << "\"_line_comment_" << lineIdx << "\": \"" << tokens[tokens.size() - 1] << "\"," << std::endl;
        }
        else {
            tokens.clear();
            split(line, jsonAssign, tokens);
            
            if (tokens.size() > 1) {
                size_t p = tokens[0].find_first_not_of(" ");
                tokens[0].insert(p, "\"");
                p = tokens[0].find_last_not_of(" ");
                tokens[0].insert(p + 1, "\"");
            
                jsonStream << tokens[0] << ":";
                for (size_t i = 1; i < tokens.size(); i++) {
                    jsonStream << " " << tokens[i];
                }
                jsonStream << std::endl;
            }
            else {
                jsonStream << line << std::endl;
            }
        }
    }

    jsonStream << "}" << std::endl;

    return jsonStream.str();
}

/**
 * serves GET requests on http://localhost/configuration - returns
 * JSON converted pokey configuration content
 */
void SimHubEventController::httpGETConfigurationHandler(web::http::http_request request)
{
    std::string config_json = libconfigToJSON(_configManager->pokeyConfigurationFilename());
    request.reply(web::http::status_codes::OK, config_json);
}

/**
 * constructs cpprest HTTP listener instance and tells it to start
 * listening on cofigured port
 */
void SimHubEventController::startHTTPListener(void)
{
    std::stringstream httpListenURI;
    
    httpListenURI << "http://" << _configManager->httpListenAddress() << ":" << _configManager->httpListenPort();
    _configurationHTTPListener = std::make_shared<web::http::experimental::listener::http_listener>(httpListenURI.str());

    // start http listener for json config read
    _configurationHTTPListener->open().wait();
    _configurationHTTPListener->support(web::http::methods::GET, std::bind(&SimHubEventController::httpGETConfigurationHandler, this, std::placeholders::_1));
}

SimHubEventController::~SimHubEventController(void)
{
    if (_running) {
        terminate();
    }

#if defined(_AWS_SDK)
    if (_awsHelper.polly()) {
        _awsHelper.polly()->shutdown();
    }

    if (_awsHelper.kinesis()) {
        _awsHelper.kinesis()->shutdown();
    }

    _awsHelper.shutdown();
#endif
}

#if defined(_AWS_SDK)
void SimHubEventController::startSustainThread(void)
{
    _awsHelper.polly()->say("Simulator is ready.");
    std::shared_ptr<std::thread> sustainThread = std::make_shared<std::thread>([=] {
        _sustainThreadManager.setThreadRunning(true);
        while (!_sustainThreadManager.threadCanceled()) {
            std::this_thread::sleep_for(100ms);

            // build up list of values that need to be resent to kinesis
            // due to expiration of their sustain timer
            std::lock_guard<std::mutex> sustainGuard(_sustainValuesMutex);

            std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

            for (std::pair<std::string, SustainMapEntry> entry: _sustainValues) {
                std::chrono::milliseconds sustain = entry.second.first;
                std::chrono::milliseconds ts = entry.second.second->timestamp();

                if ((ts + sustain) <= now) {
                    entry.second.second->resetTimestamp();
                    logger.log(LOG_INFO, "sustaining value: %s", entry.second.second->name().c_str());
                    deliverKinesisValue(entry.second.second);
                }
            }
        }
        _sustainThreadManager.setThreadRunning(false);
    });

    _sustainThreadManager.setManagedThread(sustainThread);
}

void SimHubEventController::ceaseSustainThread(void)
{
    _sustainThreadManager.shutdownThread();
}

void SimHubEventController::deliverKinesisValue(std::shared_ptr<Attribute> value)
{
    std::string name = value->name();
    std::string val = value->valueToString();
    std::string ts = value->timestampAsString();
    std::string description = value->description();
    std::string units = value->units();

    // {s:"a",t:"b",v:"123", ts:121}
    std::stringstream ss;

    ss << "{ \"s\" : \"" << name << "\", \"val\" : \"" << val << "\", \"ts\" : \"" << ts << "\", \"d\" : \"" << description << "\", \"u\":\"" << units << "\"}";
    std::string dataString = ss.str();

    Aws::Utils::ByteBuffer data(dataString.length());

    for (int i = 0; i < dataString.length(); i++) {
        data[i] = dataString[i];
    }

    _awsHelper.kinesis()->putRecord(data);
}

void SimHubEventController::enablePolly(void)
{
    _awsHelper.initPolly();
}

void SimHubEventController::enableKinesis(void)
{
    // read the configuration sections we need
    const libconfig::Setting &aws = _configManager->config()->lookup("aws");
    const libconfig::Setting &kinesis = aws.lookup("kinesis");
    // somehwere to store our variables
    std::string region;
    std::string stream;
    std::string partition;
    // read the configuration values
    aws.lookupValue("region", region);
    kinesis.lookupValue("stream", stream);
    kinesis.lookupValue("partition", partition);
    // initialise the kinesis helper
    _awsHelper.initKinesis(stream, partition, region);
}

#endif

void SimHubEventController::setConfigManager(ConfigManager *configManager)
{
    _configManager = configManager;
}

void SimHubEventController::ceaseEventLoop(void)
{
    _eventQueue.unblock();
}

bool SimHubEventController::deliverValue(std::shared_ptr<Attribute> value)
{
    assert(_pokeyMethods.simplug_deliver_value);

    GenericTLV *c_value = AttributeToCGeneric(value);

    bool retVal = false;

#if defined(_AWS_SDK)
    if (mapContains(_configManager->mapManager()->sustainMap(), value->name())) {
        // update the sustain value map entry
        std::lock_guard<std::mutex> sustainGuard(_sustainValuesMutex);
        _sustainValues[value->name()].second = value;
        _sustainValues[value->name()].first = std::chrono::milliseconds(_configManager->mapManager()->sustainMap()[value->name()]);
    }
#endif

    // determine value destination from the source - very simple at the moment
    // (just deliver to whatever instance is not the source) - may want more
    // sophisticated logic here

    if (value->ownerPlugin() == _pokeyMethods.plugin_instance) {
        retVal = !_prepare3dMethods.simplug_deliver_value(_prepare3dMethods.plugin_instance, c_value);
    }
    else if (value->ownerPlugin() == _prepare3dMethods.plugin_instance) {

#if defined(_AWS_SDK)
        if (value->name() == "N_ELEC_PANEL_LOWER_LEFT") {
                  _awsHelper.polly()->say("dc volts %i", c_value->value);
        }
#endif

        retVal = !_pokeyMethods.simplug_deliver_value(_pokeyMethods.plugin_instance, c_value);
    }

    return retVal;
}

// these callbacks will be called from the thread of the event
// generator which is assumed to not be the thread of the for loop
// below

void SimHubEventController::prepare3dEventCallback(SPHANDLE eventSource, void *eventData)
{
    // event source will pass through NULL in event of error
    if (eventData) {
        GenericTLV *data = static_cast<GenericTLV *>(eventData);
        assert(data != NULL);

        std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(data);
        MapEntry *mapEntry;

        if (_configManager->mapManager()->find(data->name, &mapEntry)) {
            _eventQueue.push(attribute);
        }

        release_generic(data);
    }
    else {
        ceaseEventLoop();
    }
}

void SimHubEventController::pokeyEventCallback(SPHANDLE eventSource, void *eventData)
{
    // event source will pass through NULL in event of error
    if (eventData) {
        GenericTLV *data = static_cast<GenericTLV *>(eventData);
        assert(data != NULL);

        std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(data);
        MapEntry *mapEntry;

        if (_configManager->mapManager()->find(data->name, &mapEntry)) {
            _eventQueue.push(attribute);
        }

        release_generic(data);
    }
    else {
        ceaseEventLoop();
    }
}

void SimHubEventController::LoggerWrapper(const int category, const char *msg, ...)
{
    // TODO: make logger a class instance member
    char buff[MAX_VA_LENGTH];
    va_list args;
    va_start(args, msg);
    vsprintf(buff, msg, args);
    va_end(args);

    logger.log(category, buff);
}

simplug_vtable SimHubEventController::loadPlugin(std::string dylibName, libconfig::Config *pluginConfig, EnqueueEventHandler eventCallback)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);

    // TODO: use correct path
    std::string fullPath("plugins/");
    fullPath += dylibName + LIB_EXT;
    int err = simplug_bootstrap(fullPath.c_str(), &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance, SimHubEventController::LoggerWrapper);

        pluginMethods.plugin_instance = pluginInstance;

        // -- temporary solution to the plugin configuration conundrom:
        //    - iterate over the list of libconfig::Setting instances we've
        //    - been given for this plugin and pass them through

        pluginMethods.simplug_config_passthrough(pluginInstance, pluginConfig);

        // TODO: add error checking

        if (pluginMethods.simplug_preflight_complete(pluginInstance) == 0) {
            // proxy the C style lambda call through to the member
            // function above
            pluginMethods.simplug_commence_eventing(pluginInstance, eventCallback, this);
        }
        else {
            pluginMethods.simplug_release(pluginInstance);
            pluginMethods.plugin_instance = NULL;
        }
    }

    return pluginMethods;
}

bool SimHubEventController::loadPrepare3dPlugin(void)
{
    auto prepare3dCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->prepare3dEventCallback(eventSource, eventData); };

    _prepare3dMethods = loadPlugin("libprepare3d", _prepare3dDeviceConfig, prepare3dCallback);

    return _prepare3dMethods.plugin_instance != NULL;
}

bool SimHubEventController::loadPokeyPlugin(void)
{
    auto pokeyCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->pokeyEventCallback(eventSource, eventData); };

    _pokeyMethods = loadPlugin("libpokey", _pokeyDeviceConfig, pokeyCallback);

    return _pokeyMethods.plugin_instance != NULL;
}

//! perform shutdown ceremonies on both plugins - this unloads both plugins
void SimHubEventController::terminate(void)
{
    assert(_running);

#if defined(_AWS_SDK)
    ceaseSustainThread();
#endif

    // kill web configuration listener
    auto listenerCloseTask = _configurationHTTPListener->close();
    listenerCloseTask.wait();

    shutdownPlugin(_prepare3dMethods);
    shutdownPlugin(_pokeyMethods);
    
    _running = false;
}

//! private support method - gracefully closes plugin instance represented by pluginMethods
void SimHubEventController::shutdownPlugin(simplug_vtable &pluginMethods)
{
    if (pluginMethods.plugin_instance) {
        pluginMethods.simplug_cease_eventing(pluginMethods.plugin_instance);
        pluginMethods.simplug_release(pluginMethods.plugin_instance);
        pluginMethods.plugin_instance = NULL;
    }
}
