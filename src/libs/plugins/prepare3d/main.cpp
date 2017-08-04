#include <assert.h>
#include <iostream>
#include <memory>
#include <vector>

#include "common/simhubdeviceplugin.h"
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

    if (!(_rawBuffer = (char *)malloc(BUFFER_LEN))) {
        printf("Unable to allocate buffer of size %d", BUFFER_LEN);
    }
    else {
        _readBuffer = ::uv_buf_init(_rawBuffer, BUFFER_LEN);
    }
}

SimSourcePluginStateManager::~SimSourcePluginStateManager(void)
{
    // TODO: enable once shtudown implemented
    if (_pluginThread != NULL) {
        if (_pluginThread->joinable()) {
            ceaseEventing();
            _pluginThread->join();
        }

        delete _pluginThread;
    }

    if (_rawBuffer != NULL)
        free(_rawBuffer);
}

int SimSourcePluginStateManager::preflightComplete(void)
{
    int retVal = PREFLIGHT_OK;

    struct sockaddr_in req_addr;

    _eventLoop = uv_default_loop();
    check_uv(uv_loop_init(_eventLoop));

    check_uv(uv_tcp_init(_eventLoop, &_tcpClient));
    uv_tcp_keepalive(&_tcpClient, 1, 60);
    uv_ip4_addr("127.0.0.1", 8080, &req_addr);

    int connectErr = uv_tcp_connect(&_connectReq, &_tcpClient, (struct sockaddr *)&req_addr, &SimSourcePluginStateManager::OnConnect);

    if (connectErr < 0) {
        retVal = PREFLIGHT_FAIL;
    }

    return retVal;
}

void SimSourcePluginStateManager::OnConnect(uv_connect_t *req, int status)
{
    assert(SimSourcePluginStateManager::StateManagerInstance());

    if (status == SIM_CONNECT_NOT_FOUND) {
        SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_ERROR, "   - Failed to connect to simulator");
    }
    else {
        SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, " - Connected to simulator %d", status);
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
            ceaseEventing();
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
                char *buffer = (char *)malloc(1024);
                memset(buffer, 0, 1024);
                strncpy(buffer, p, len);
                buffer[len] = '\0';
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
    char *value = strtok(NULL, "=");

    if (value == NULL)
        return;

    char *type = getElementDataType(name[0]);

    if (type != NULL) {
        // SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, "%s %s %s", name, value, type);
        simElement el;

        el.name = name;

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
        else if (strncmp(type, "bool", sizeof(&type)) == 0) {
            el.type = CONFIG_BOOL;
            el.length = sizeof(int);

            if (strncmp(value, "OFF", sizeof(el.value)) == 0)
                el.value.bool_value = 0;
            else
                el.value.bool_value = 1;
        }
        _enqueueCallback(this, (void *)&el, _callbackArg);
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
    default:
        return NULL;
    }

    return NULL;
}

void SimSourcePluginStateManager::instanceCloseHandler(uv_handle_t *handle)
{
    if (!_eventLoop->active_handles) {
        uv_stop(_eventLoop);
    }
}

void SimSourcePluginStateManager::ceaseEventing(void)
{
    uv_stop(_eventLoop);
}

void SimSourcePluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    _enqueueCallback = enqueueCallback;
    _callbackArg = arg;

    // this is wrong in a number of ways - it needs to be cancel-able being its chief sin
    // TODO: unbreak
    _pluginThread = new std::thread([=] { check_uv(uv_run(_eventLoop, UV_RUN_DEFAULT)); });
}
