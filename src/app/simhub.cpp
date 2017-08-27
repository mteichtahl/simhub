#include <assert.h>
#include <utility>

#include "common/configmanager/configmanager.h"
#include "log/clog.h"
#include "simhub.h"

// TODO: FIX EVERYTHING

std::shared_ptr<SimHubEventController> SimHubEventController::_EventControllerInstance = NULL;

//! static singleton accessor
std::shared_ptr<SimHubEventController> SimHubEventController::EventControllerInstance(void)
{
    if (!_EventControllerInstance)
        _EventControllerInstance.reset(new SimHubEventController());

    return SimHubEventController::_EventControllerInstance;
}

SimHubEventController::SimHubEventController()
{
    _prepare3dMethods.plugin_instance = NULL;
    _pokeyMethods.plugin_instance = NULL;
    _configManager = NULL;
    _sustainThreadCount = 0;
    _terminated = false;

#if defined(_AWS_SDK)
    _awsHelper.init();
#endif

    logger.log(LOG_INFO, "Starting event controller");
}

SimHubEventController::~SimHubEventController(void)
{
    if (!_terminated)
        terminate();
}

void SimHubEventController::startSustainThreads(void)
{
#if defined(_AWS_SDK)
    _awsHelper.polly()->say("Simulator is ready.");
#endif

    _continueSustainThreads = true;

    for (auto sustainEntry : _configManager->mapManager()->sustainMap()) {
        _sustainThreads[sustainEntry.first] = std::make_shared<std::thread>([=] {
            _sustainThreadCount++;
            while (_continueSustainThreads) {
                sleep(1);
            }
            _sustainThreadCount--;
        });
    }
}

void SimHubEventController::ceaseSustainThreads(void)
{
    _continueSustainThreads = false;

    do {
        // noop
    } while (_sustainThreadCount > 0);

    for (auto item : _sustainThreads) {
        item.second->join();
    }
    _sustainThreads.clear();
}

#if defined(_AWS_SDK)
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

    for (int i = 0; i < dataString.length(); i++)
        data[i] = dataString[i];

    _awsHelper.kinesis()->putRecord(data);
}

void SimHubEventController::enablePolly(void)
{
    _awsHelper.initPolly();
}

void SimHubEventController::enableKinesis(void)
{
    //! read the configuration sections we need
    const libconfig::Setting &aws = _configManager->config()->lookup("aws");
    const libconfig::Setting &kinesis = aws.lookup("kinesis");
    //! somehwere to store our variables
    std::string region;
    std::string stream;
    std::string partition;
    //! read the configuration values
    aws.lookupValue("region", region);
    kinesis.lookupValue("stream", stream);
    kinesis.lookupValue("partition", partition);
    //! initialise the kinesis helper
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

    // determine value destination from the source - very simple at the moment
    // (just deliver to whatever instance is not the source) - may want more
    // sophisticated logic here

    if (value->ownerPlugin() == _pokeyMethods.plugin_instance)
        retVal = !_prepare3dMethods.simplug_deliver_value(_prepare3dMethods.plugin_instance, c_value);
    else if (value->ownerPlugin() == _prepare3dMethods.plugin_instance) {

        if (value->name() == "N_ELEC_PANEL_LOWER_LEFT") {
            if (c_value >= 0)
                _awsHelper.polly()->say("dc volts %i", c_value->value);
        }

        retVal = !_pokeyMethods.simplug_deliver_value(_pokeyMethods.plugin_instance, c_value);
    }

    if (c_value->type == CONFIG_STRING)
        free(c_value->value.string_value);
    free(c_value->name);
    free(c_value);

    return retVal;
}
// these callbacks will be called from the thread of the event
// generator which is assumed to not be the thread of the for
// loop below

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
    ceaseSustainThreads();
    shutdownPlugin(_prepare3dMethods);
    shutdownPlugin(_pokeyMethods);

#if defined(_AWS_SDK)
    _awsHelper.polly()->shutdown();
    _awsHelper.kinesis()->shutdown();

    _awsHelper.shutdown();
#endif

    _terminated = true;
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
