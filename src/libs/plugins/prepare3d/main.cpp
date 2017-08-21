#include <assert.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "common/simhubdeviceplugin.h"
#include "elements/attributes/attribute.h"
#include "main.h"

// -- public C FFI

extern "C" {
int simplug_init(SPHANDLE *plugin_instance, LoggingFunctionCB logger)
{
    *plugin_instance = new SimSourcePluginStateManager(logger);
    return 0;
}

int simplug_config_passthrough(SPHANDLE plugin_instance, void *libconfig_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->configPassthrough(static_cast<libconfig::Config *>(libconfig_instance));
}

int simplug_preflight_complete(SPHANDLE plugin_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->preflightComplete();
}

void simplug_commence_eventing(SPHANDLE plugin_instance, EnqueueEventHandler enqueue_callback, void *arg)
{
    static_cast<PluginStateManager *>(plugin_instance)->commenceEventing(enqueue_callback, arg);
}

int simplug_deliver_value(SPHANDLE plugin_instance, GenericTLV *value)
{
    return static_cast<PluginStateManager *>(plugin_instance)->deliverValue(value);
}

void simplug_cease_eventing(SPHANDLE plugin_instance)
{
    static_cast<PluginStateManager *>(plugin_instance)->ceaseEventing();
}

void simplug_release(SPHANDLE plugin_instance)
{
    assert(plugin_instance);
    delete static_cast<PluginStateManager *>(plugin_instance);
}
}

// -- internal implementation

SimSourcePluginStateManager *SimSourcePluginStateManager::_StateManagerInstance = NULL;

void SimSourcePluginStateManager::AllocBuffer(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    *buf = SimSourcePluginStateManager::StateManagerInstance()->_readBuffer;
}

//! static getter for singleton instance of our class
SimSourcePluginStateManager *SimSourcePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

SimSourcePluginStateManager::SimSourcePluginStateManager(LoggingFunctionCB logger)
    : PluginStateManager(logger)
{
    // enforce singleton pre-condition

    assert(!_StateManagerInstance);

    _StateManagerInstance = this;
    _processedElementCount = 0;
    _name = "prepar3d";

    if (!(_rawBuffer = (char *)malloc(BUFFER_LEN))) {
        printf("Unable to allocate buffer of size %d", BUFFER_LEN);
    }
    else {
        _readBuffer = ::uv_buf_init(_rawBuffer, BUFFER_LEN);
    }
}

SimSourcePluginStateManager::~SimSourcePluginStateManager(void)
{
    ceaseEventing();
    if (_rawBuffer != NULL)
        free(_rawBuffer);
}

int SimSourcePluginStateManager::preflightComplete(void)
{
    int retVal = PREFLIGHT_OK;
    int port = 8091;

    libconfig::Setting *devicesConfiguraiton = NULL;

    std::string type = "";
    std::string ipAddress = "";

    try {
        devicesConfiguraiton = &_config->lookup("configuration");
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
    }

    for (libconfig::SettingIterator iter = devicesConfiguraiton->begin(); iter != devicesConfiguraiton->end(); iter++) {

        if (iter->exists("ipAddress")) {
            iter->lookupValue("ipAddress", ipAddress);
        }
        else {
            ipAddress = "127.0.0.1";
        }

        if (iter->exists("port")) {
            iter->lookupValue("port", port);
        }

        if (iter->exists("transforms")) {
            loadTransforms(&iter->lookup("transforms"));
        }
    }

    _logger(LOG_ERROR, "Connecting to simulator on %s:%d.", ipAddress.c_str(), port);

    struct sockaddr_in req_addr;

    _eventLoop = uv_default_loop();
    check_uv(uv_loop_init(_eventLoop));
    check_uv(uv_tcp_init(_eventLoop, &_tcpClient));
    uv_tcp_keepalive(&_tcpClient, 1, 60);

    uv_ip4_addr(ipAddress.c_str(), port, &req_addr);

    // so the callback can see member values
    _connectReq.data = this;

    int connectErr = uv_tcp_connect(&_connectReq, &_tcpClient, (struct sockaddr *)&req_addr, &SimSourcePluginStateManager::OnConnect);

    if (connectErr < 0) {
        retVal = PREFLIGHT_FAIL;
    }

    // connect to simulated prosim listener
    _sendSocketClient.setLogger(_logger);
    if (retVal != PREFLIGHT_FAIL && !_sendSocketClient.connect(ipAddress, port)) {
        retVal = PREFLIGHT_FAIL;
    }

    return retVal;
}

std::string SimSourcePluginStateManager::transformBoolToString(std::string orginalValue, std::string transformResultOff, std::string transformResultOn)
{
    if (orginalValue == "0") {
        return transformResultOff;
    }
    else {
        return transformResultOn;
    }
    return "";
}

void SimSourcePluginStateManager::loadTransforms(libconfig::Setting *transforms)
{
    _logger(LOG_INFO, "Loading %i transforms ", transforms->getLength());

    for (libconfig::Setting const &transform : *transforms) {
        std::string transformName = transform.getName();

        _logger(LOG_INFO, " - transform %s", transformName.c_str());

        if (transform.exists("On") && transform.exists("Off")) {
            std::string transformResultOn;
            std::string transformResultOff;
            transform.lookupValue("On", transformResultOn);
            transform.lookupValue("Off", transformResultOff);
            _transformMap.emplace(
                transformName, std::bind(&SimSourcePluginStateManager::transformBoolToString, this, std::placeholders::_1, transformResultOff, transformResultOn));
        }
    }
}

/**
 *   @brief  Default  find a transform by element name
 *
 *   @return TransformFunction or NULL if not found
 */
TransformFunction SimSourcePluginStateManager::transform(std::string transformName)
{
    TransformMap::iterator it = _transformMap.find(transformName);

    if (it != _transformMap.end()) {
        return (*it).second;
    }

    return NULL;
}

void SimSourcePluginStateManager::OnConnect(uv_connect_t *req, int status)
{
    assert(SimSourcePluginStateManager::StateManagerInstance());

    SimSourcePluginStateManager *self = static_cast<SimSourcePluginStateManager *>(req->data);

    if (status == SIM_CONNECT_NOT_FOUND) {
        SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_ERROR, "   - Failed to connect to simulator");
        // deliver NULL value to indicate failure to app
        self->_enqueueCallback(self, (void *)NULL, self->_callbackArg);
    }
    else {
        SimSourcePluginStateManager::StateManagerInstance()->instanceConnectionHandler(req, status);
    }
}

void SimSourcePluginStateManager::OnRead(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf)
{
    SimSourcePluginStateManager::StateManagerInstance()->instanceReadHandler(server, nread, buf);
}

void SimSourcePluginStateManager::OnClose(uv_handle_t *handle)
{
    assert(SimSourcePluginStateManager::StateManagerInstance());
    SimSourcePluginStateManager::StateManagerInstance()->instanceCloseHandler(handle);
}

void SimSourcePluginStateManager::instanceConnectionHandler(uv_connect_t *req, int status)
{
    if (uv_is_readable(req->handle)) {
        uv_read_start(req->handle, &SimSourcePluginStateManager::AllocBuffer, &SimSourcePluginStateManager::OnRead);
    }
    else {
        printf("not readable\n");
    }
}

void SimSourcePluginStateManager::instanceReadHandler(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0) {
        uv_buf_t buffer = uv_buf_init((char *)malloc(nread), nread);
        memcpy(buffer.base, buf->base, nread);
        buffer.base[nread - 1] = '\0';
        processData(buffer.base, nread);
        free(buffer.base);
    }
    else if (nread < 0) {
        if (nread == UV_EOF) {
            SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, " - Stopping prepare3d ingest loop");
            stopUVLoop();
            // deliver NULL value to indicate failure to app
            _enqueueCallback(this, (void *)NULL, _callbackArg);
        }
        else {
            SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, " - %s", uv_strerror(nread));
            uv_close((uv_handle_t *)server, &SimSourcePluginStateManager::OnClose);
        }
    }
}

void SimSourcePluginStateManager::processData(char *data, int len)
{
    if (len > 2) {
        int elementCount = 0;
        char *p = strtok(data, "\n");
        char *array[MAX_ELEMENTS_PER_UPDATE];

        while (p != NULL) {
            size_t len = strlen(p);

            if (len > 2) {
                char *buffer = (char *)malloc(BUFFER_LEN);
                memset(buffer, 0, BUFFER_LEN);
                strncpy(buffer, p, len);
                buffer[len - 1] = '\0';
                array[elementCount++] = buffer;
            }

            p = strtok(NULL, "\n");
        }

        for (int i = 0; i < elementCount; ++i) {
            processElement(array[i]);
            free(array[i]);
        }
    }
}

void SimSourcePluginStateManager::processElement(char *element)
{

    char *name = strtok(element, "=");
    char *value = strtok(NULL, " =");
    name[strlen(name) - 1] = '\0';

    if (value == NULL)
        return;

    char *type = getElementDataType(name[0]);

    if (type != NULL) {
        GenericTLV el;

        el.name = name;
        el.ownerPlugin = this;

        if (strncmp(type, "float", sizeof(&type)) == 0) {
            el.type = CONFIG_FLOAT;
            el.value.float_value = atof(value);
            el.length = sizeof(float);
        }
        else if (strncmp(type, "char", sizeof(&type)) == 0) {
            el.type = CONFIG_STRING;
            el.value.string_value = value;
            el.length = strlen(value);
        }
        else if (strncmp(type, "integer", sizeof(&type)) == 0) {
            el.type = CONFIG_INT;
            el.value.int_value = atoi(value);
            el.length = sizeof(int);
        }
        else if (strncmp(type, "uint", sizeof(&type)) == 0) {
            el.type = CONFIG_UINT;
            el.value.int_value = (uint)atoi(value);
            el.length = sizeof(int);
        }
        else if (strncmp(type, "bool", sizeof(&type)) == 0) {
            el.type = CONFIG_BOOL;
            el.length = sizeof(uint8_t);

            if (strncmp(value, "0", sizeof(el.value)) == 0) {
                el.value.bool_value = 0;
            }
            else {
                el.value.bool_value = 1;
            }
        }
        else {
            _logger(LOG_ERROR, "Missing prosim type mapping %s %s %s", name, value, type);
        }

        _enqueueCallback(this, (void *)&el, _callbackArg);

        // TODO remove this echo test - or make it a configuartion switch
        // deliverValue(&el);

        _processedElementCount++;
    }
}

char *SimSourcePluginStateManager::getElementDataType(char identifier)
{
    switch (identifier) {
    case GAUGE_IDENTIFIER:
        return (char *)"float";
        break;
    case NUMBER_IDENTIFIER:
        return (char *)"float";
        break;
    case INDICATOR_IDENTIFIER:
        return (char *)"bool";
        break;
    case VALUE_IDENTIFIER:
        return (char *)"uint";
        break;
    case ANALOG_IDENTIFIER:
        return (char *)"char";
        break;
    case ROTARY_IDENTIFIER:
        return (char *)"char";
        break;
    case BOOLEAN_IDENTIFIER:
        return (char *)"bool";
        break;
    case SWITCH_IDENTIFIER:
        return (char *)"bool";
        break;
    default:
        _logger(LOG_ERROR, "Missing prosim element data type %c", identifier);
        break;
    }

    return (char *)"char";
}

std::string SimSourcePluginStateManager::prosimValueString(std::shared_ptr<Attribute> attribute)
{
    std::string retVal("");

    // TODO: look at first char of target and use this to
    // validate the type of attribute and to convert the
    // attribute value to a prosim value string

    switch (attribute->name().c_str()[0]) {
    case SWITCH_IDENTIFIER:
        retVal = attribute->getValue<bool>() ? 0 : 1;
        break;

    default:
        retVal = attribute->getValueToString();
        break;
    }

    return retVal;
}

int SimSourcePluginStateManager::deliverValue(GenericTLV *value)
{
    std::ostringstream oss;
    std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(value);

    TransformFunction transformFunction = transform(attribute->name());

    if (transformFunction) {
        std::string val = transformFunction(attribute->getValueToString(), "NULL", "NULL");
        oss << attribute->name() << "=" << val << "\n";
    }
    else {
        oss << attribute->name() << "=" << prosimValueString(attribute) << "\n";
    }

    _logger(LOG_INFO, "[%s] %s", attribute->name().c_str(), attribute->description().c_str());

    _sendSocketClient.sendData(oss.str());

    return 0;
}

void SimSourcePluginStateManager::instanceCloseHandler(uv_handle_t *handle)
{
    if (!_eventLoop->active_handles) {
        stopUVLoop();
    }
}

void SimSourcePluginStateManager::stopUVLoop(void)
{
    if (_eventLoop) {
        uv_stop(_eventLoop);
        uv_loop_close(_eventLoop);
        _eventLoop = NULL;
    }
}

void SimSourcePluginStateManager::ceaseEventing(void)
{
    if (_pluginThread) {
        stopUVLoop();

        if (_pluginThread->joinable()) {
            _pluginThread->join();
        }
    }
}

void SimSourcePluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    _enqueueCallback = enqueueCallback;
    _callbackArg = arg;
    _pluginThread = std::make_shared<std::thread>([=] { check_uv(uv_run(_eventLoop, UV_RUN_DEFAULT)); });
}

// -- simple socket send/receive wrapper

TCPClient::TCPClient(void)
{
    _sock = -1;
    _port = 0;
    _address = "";
}

void TCPClient::setLogger(LoggingFunctionCB logger)
{
    _logger = logger;
}

/**
    Connect to a host on a certain port number
*/
bool TCPClient::connect(std::string address, int port)
{
    _address = address;
    _port = port;

    // create socket if it is not already created
    if (_sock == -1) {
        _sock = socket(AF_INET, SOCK_STREAM, 0);
        if (_sock == -1)
            perror("Could not create socket");
    }

    // setup address structure
    if (inet_addr(_address.c_str()) == -1) {
        struct hostent *he;
        struct in_addr **addr_list;

        // resolve the hostname, its not an ip address
        if ((he = gethostbyname(_address.c_str())) == NULL) {
            herror("gethostbyname");
            std::cout << "Failed to resolve hostname" << std::endl;
            return false;
        }

        // cast the h_addr_list to in_addr , since h_addr_list also has the ip
        // address in long format only
        addr_list = (struct in_addr **)he->h_addr_list;
        for (int i = 0; addr_list[i] != NULL; i++) {
            _server.sin_addr = *addr_list[i];
            std::cout << address << " resolved to " << inet_ntoa(*addr_list[i]) << std::endl;
            break;
        }
    }
    else {
        _server.sin_addr.s_addr = inet_addr(address.c_str());
    }

    _server.sin_family = AF_INET;
    _server.sin_port = htons(port);

    // connect to remote server
    if (::connect(_sock, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    _logger(LOG_INFO, " - Connected to %s", address.c_str());
    return true;
}

/**
    Send data to the connected host
*/
bool TCPClient::sendData(std::string data)
{
    // Send some data
    if (send(_sock, data.c_str(), data.size(), 0) < 0) {
        perror("Send failed : ");
        return false;
    }
    return true;
}

/**
    Receive data from the connected host
*/
std::string TCPClient::receive(int size = 512)
{
    char buffer[size];
    std::string reply;

    // Receive a reply from the server
    if (recv(_sock, buffer, sizeof(buffer), 0) < 0)
        puts("recv failed");

    reply = buffer;
    return reply;
}
