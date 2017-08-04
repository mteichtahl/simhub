#ifndef __PLUGINSTATEMANAGER_H
#define __PLUGINSTATEMANAGER_H

#include <libconfig.h++>
#include <list>
#include <thread>

#include "common/simhubdeviceplugin.h"

#define PREFLIGHT_OK 0
#define PREFLIGHT_FAIL 1

enum logCategory { LOG_INFO = 1, LOG_ERROR = 2, LOG_DEBUG = 3 };

/**
 * This base class serves as the definition of shared supporting
 * functionality that can be used to create specific plugin
 * implementations - for use within the guts of the plugin
 * implementation, not exposed to the C FFI.
 *
 * Currently has very simple stub implementations of these methods for
 * the purposes of demonstration - eventually some of these
 * implementations should be removed in favour of abstract (pure
 * virtual) methods.
 */
class PluginStateManager
{
protected:
    virtual void runTestEventLoop(void);
    EnqueueEventHandler _enqueueCallback;
    std::thread _testEventThread;
    void *_callbackArg;
    LoggingFunctionCB _logger;

    //! config for use in preflightComplete
    libconfig::Config *_config;

public:
    PluginStateManager(LoggingFunctionCB logger);
    virtual ~PluginStateManager(void);

    virtual int configPassthrough(libconfig::Config *pluginConfiguration);
    virtual int preflightComplete(void);
    virtual void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    virtual int deliverValue(GenericTLV *value);
    virtual void ceaseEventing(void);
};

#endif
