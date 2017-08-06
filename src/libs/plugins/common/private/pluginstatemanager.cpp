#include <iostream>
#include <unistd.h>

#include "pluginstatemanager.h"

PluginStateManager::PluginStateManager(LoggingFunctionCB logger)
    : _enqueueCallback(NULL)
    , _logger(logger)
{
}

PluginStateManager::~PluginStateManager(void)
{
}

void PluginStateManager::runTestEventLoop(void)
{
    std::cout << "generating 9 events in a sleep loop" << std::endl;
    for (size_t i = 0; i < 9; i++) {
        sleep(1);
        _enqueueCallback(this, (void *)"echo", _callbackArg);
    }
    std::cout << "done" << std::endl;
}

//! just queue up a copy of the device settings for use in preflightComplete
int PluginStateManager::configPassthrough(libconfig::Config *pluginConfiguration)
{
    _config = pluginConfiguration;
    return 0;
}

int PluginStateManager::preflightComplete(void)
{
    return 0;
}

int PluginStateManager::deliverValue(GenericTLV *value)
{
    return 0;
}

void PluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    _logger(LOG_INFO, "  - commence eventing");
    _enqueueCallback = enqueueCallback;
    _callbackArg = arg;
    //_testEventThread = std::thread(std::bind(&PluginStateManager::runTestEventLoop, this));
}

void PluginStateManager::ceaseEventing(void)
{
    _logger(LOG_INFO, "  - Cease eventing");
}
