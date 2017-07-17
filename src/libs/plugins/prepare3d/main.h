#ifndef __SIMSOURCE_MAIN_H
#define __SIMSOURCE_MAIN_H

#include "common/private/pluginstatemanager.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

void onConnect(uv_connect_t *req, int status)
{
    if (uv_is_readable(req->handle)) {
        printf("reading\n");
        //    uv_read_start(req->handle, alloc_buffer, onRead);
    }
    else {
        printf("not readable\n");
    }
}

#define BUFFER_LEN 4096

#define check_uv(status)                                                                                                                                                           \
    do {                                                                                                                                                                           \
        int code = (status);                                                                                                                                                       \
        if (code < 0) {                                                                                                                                                            \
            fprintf(stderr, "%s: %s\n", uv_err_name(code), uv_strerror(code));                                                                                                     \
            exit(code);                                                                                                                                                            \
        }                                                                                                                                                                          \
    } while (0)

//! barest specialisation of the internal plugin management support base class
class SimSourcePluginStateManager : public PluginStateManager
{
public:
    SimSourcePluginStateManager(void);
    int preflightComplete(void);
    void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    void ceaseEventing(void);

private:
    uv_loop_t *_eventLoop; ///< main libuv event loop
    uv_buf_t _read_buffer; ///< tcp read buffer
    uv_tcp_t _tcp_client; ///< tcp_client
    uv_connect_t _connect_req;

    char *_raw_buffer; ///< raw buffer for the tcp loop

    void onConnect(uv_connect_t *req, int status);
    void onRead(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf);
    void onClose(uv_handle_t *handle);
};

SimSourcePluginStateManager::SimSourcePluginStateManager()
{
    if (!(_raw_buffer = (char *)malloc(BUFFER_LEN))) {
        printf("Unable to allocate buffer of size %d", BUFFER_LEN);
    }
    else {
        _read_buffer = ::uv_buf_init(_raw_buffer, BUFFER_LEN);
    }
}

int SimSourcePluginStateManager::preflightComplete(void)
{
    struct sockaddr_in req_addr;

    _eventLoop = uv_default_loop();
    check_uv(uv_loop_init(_eventLoop));

    check_uv(uv_tcp_init(_eventLoop, &_tcp_client));
    uv_tcp_keepalive(&_tcp_client, 1, 60);
    uv_ip4_addr("127.0.0.1", 8080, &req_addr);
    uv_tcp_connect(&_connect_req, &_tcp_client, (struct sockaddr *)&req_addr, &::onConnect);

    return PREFLIGHT_OK;
}

void SimSourcePluginStateManager::onConnect(uv_connect_t *req, int status)
{
    if (uv_is_readable(req->handle)) {
        //    uv_read_start(req->handle, alloc_buffer, onRead);
    }
    else {
        printf("not readable\n");
    }
}

void SimSourcePluginStateManager::onRead(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf)
{
}

void SimSourcePluginStateManager::ceaseEventing(void)
{
}

void SimSourcePluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
}

#endif
