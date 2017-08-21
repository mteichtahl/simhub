#include <iostream>
#include <unistd.h>

#include "pluginstatemanager.h"

PluginStateManager::PluginStateManager(LoggingFunctionCB logger)
    : _enqueueCallback(NULL)
    , _logger(logger)
    , _pluginThread(NULL)
{
}

PluginStateManager::~PluginStateManager(void) {}

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
}

void PluginStateManager::ceaseEventing(void)
{
    _logger(LOG_INFO, "  - Cease eventing");
}
