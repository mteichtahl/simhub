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
    *buf = SimSourcePluginStateManager::StateManagerInstance()->_readBuffer;;
}

SimSourcePluginStateManager * SimSourcePluginStateManager::_StateManagerInstance = NULL;

//! static getter for singleton instance of our class

SimSourcePluginStateManager * SimSourcePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

SimSourcePluginStateManager::SimSourcePluginStateManager(LoggingFunctionCB logger) 
    : PluginStateManager(logger)
{
    // enforce singleton pre-condition

    assert(!_StateManagerInstance);

    _StateManagerInstance = this;

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

    std::cout << "adding connection handler" << std::endl;
    int connectErr = uv_tcp_connect(&_connectReq, &_tcpClient, (struct sockaddr *)&req_addr, &SimSourcePluginStateManager::OnConnect);

    if (connectErr != 0) {
        retVal = PREFLIGHT_FAIL;
    }

    return retVal;
}

void SimSourcePluginStateManager::OnConnect(uv_connect_t *req, int status)
{
    assert(SimSourcePluginStateManager::StateManagerInstance());
    SimSourcePluginStateManager::StateManagerInstance()->_logger(2, "hola amiga (%d)!", status);
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
        std::cout << "read " << nread << " size buffered data" << std::endl;
        std::cout << "stringified buffer: ";

        for (int i = 0; i < nread; i++) {
            std::cout << buf->base[i];
        }

        std::cout << std::endl;
    }
    else if (nread < 0)
    {
        if (nread == UV_EOF) {
            printf("STOPPING LOOP\n");
            ceaseEventing();
        }
        else {
            printf("%s\n", uv_strerror(nread));
            uv_close((uv_handle_t *)server, &SimSourcePluginStateManager::OnClose);
        }
    }
}

void SimSourcePluginStateManager::instanceCloseHandler(uv_handle_t *handle)
{
    if (!_eventLoop->active_handles)
    {
        uv_stop(_eventLoop);
    }
}

void SimSourcePluginStateManager::ceaseEventing(void)
{
    uv_stop(_eventLoop);
}

void SimSourcePluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    check_uv(uv_run(_eventLoop, UV_RUN_DEFAULT));
}

