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
private:
    uv_loop_t *_eventLoop; ///< main libuv event loop
    uv_buf_t _readBuffer; ///< tcp read buffer
    uv_tcp_t _tcpClient; ///< tcp_client
    uv_connect_t _connectReq;
    char *_rawBuffer; ///< raw buffer for the tcp loop

    //! simple implementation of class instance singleton
    static SimSourcePluginStateManager *_StateManagerInstance;

    static SimSourcePluginStateManager *StateManagerInstance(void);
    static void AllocBuffer(uv_handle_t *handle, size_t size, uv_buf_t *buf);

    // wraps C style for instance methods instance*
    static void OnRead(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf);
    static void OnClose(uv_handle_t *handle);
    static void OnConnect(uv_connect_t *req, int status);

    void instanceReadHandler(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf);
    void instanceCloseHandler(uv_handle_t *handle);
    void instanceConnectionHandler(uv_connect_t *req, int status);


public:
    SimSourcePluginStateManager(LoggingFunctionCB logger);
    int preflightComplete(void);
    void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    void ceaseEventing(void);
};

#endif
