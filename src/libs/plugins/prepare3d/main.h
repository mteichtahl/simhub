#ifndef __SIMSOURCE_MAIN_H
#define __SIMSOURCE_MAIN_H

#include "common/private/pluginstatemanager.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <uv.h>

#define BUFFER_LEN 4096
#define MAX_ELEMENTS_PER_UPDATE 512
#define GAUGE_IDENTIFIER 'G'
#define NUMBER_IDENTIFIER 'N'
#define INDICATOR_IDENTIFIER 'I'
#define VALUE_IDENTIFIER 'V'
#define ANALOG_IDENTIFIER 'A'
#define ROTARY_IDENTIFIER 'R'
#define BOOLEAN_IDENTIFIER 'B'

#define SIM_CONNECT_NOT_FOUND -61

typedef GenericTLV simElement;

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

    // statistics
    long _processedElementCount;

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

    // data element processing
    void processData(char *data, int len);
    void processElement(char *element);
    char *getElementDataType(char identifier);
    std::thread *_pluginThread;

public:
    SimSourcePluginStateManager(LoggingFunctionCB logger);
    virtual ~SimSourcePluginStateManager(void);

    int preflightComplete(void);
    void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    void ceaseEventing(void);
};

#endif
