#include <assert.h>
#include <iostream>

#include "common/simhubdeviceplugin.h"
#include "main.h"

// -- public C FFI

extern "C" {
int simplug_init(SPHANDLE *plugin_instance, LoggingFunctionCB logger)
{
    *plugin_instance = new SimSourcePluginStateManager(logger);
    return 0;
}

int simplug_bind_config_values(SPHANDLE plugin_instance, char *group_name, ConfigEntry **values, int count)
{
    return static_cast<PluginStateManager *>(plugin_instance)->bindConfigValues(group_name, values, count);
}

int simplug_preflight_complete(SPHANDLE plugin_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->preflightComplete();
}
void simplug_commence_eventing(SPHANDLE plugin_instance, EnqueueEventHandler enqueue_callback, void *arg)
{
    static_cast<PluginStateManager *>(plugin_instance)->commenceEventing(enqueue_callback, arg);
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

void SimSourcePluginStateManager::AllocBuffer(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    *buf = SimSourcePluginStateManager::StateManagerInstance()->_readBuffer;
    ;
}

SimSourcePluginStateManager *SimSourcePluginStateManager::_StateManagerInstance = NULL;

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

    if (connectErr != 0) {
        retVal = PREFLIGHT_FAIL;
    }

    return retVal;
}

void SimSourcePluginStateManager::OnConnect(uv_connect_t *req, int status)
{
    assert(SimSourcePluginStateManager::StateManagerInstance());

    SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, " - Connected to simulator %d", status);
    SimSourcePluginStateManager::StateManagerInstance()->instanceConnectionHandler(req, status);
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
        processData(buffer.base, nread);
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
    int elementCount = 0;
    char *p = strtok(data, "\n\r");
    char *array[MAX_ELEMENTS_PER_UPDATE];

    while (p != NULL) {
        array[elementCount++] = p;
        p = strtok(NULL, "\n\r");
    }

    for (int i = 0; i < elementCount; ++i)
        processElement(i, array[i]);
}

void SimSourcePluginStateManager::processElement(int index, char *element)
{
    char *name = strtok(element, "=");
    char *value = strtok(NULL, "=");

    if (value == NULL)
        return;

    char *type = getElementDataType(name[0]);

    if (type != NULL) {
        SimSourcePluginStateManager::StateManagerInstance()->_logger(LOG_INFO, "%s %s %s", name, value, type);

        // Source el("element", "desc");
        // Attribute attr;
        // attr._name = "at1name";
        // attr._description = "lkfjdslfjkds";
        // attr._type = FLOAT_ATTRIBUTE;
        // attr.setValue<float>(1.223);

        // el.addAttribute(attr);
        _enqueueCallback(this, (void *)name, _callbackArg);
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
    check_uv(uv_run(_eventLoop, UV_RUN_DEFAULT));
}
