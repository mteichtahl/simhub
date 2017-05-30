#include <iostream>
#include <unistd.h>

#include "pluginstatemanager.h"

PluginStateManager::PluginStateManager(void)
    : _enqueueCallback(NULL)
{
    std::cout << "simplugin init'd" << std::endl;
    _testEventThread = std::thread(std::bind(&PluginStateManager::runTestEventLoop, this));
}

PluginStateManager::~PluginStateManager(void)
{
    std::cout << "simplugin release" << std::endl;
    _testEventThread.join();
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

int PluginStateManager::bindConfigValues(char *group_name, ConfigEntry **values, int count)
{
    std::cout << "bindConfigValues: " << group_name << ", " << count << std::endl;
    return 0;
}

int PluginStateManager::preflightComplete(void)
{
    return 0;
}

void PluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    std::cout << "commence eventing" << std::endl;
    _enqueueCallback = enqueueCallback;
    _callbackArg = arg;
}

void PluginStateManager::ceaseEventing(void)
{
    std::cout << "cease eventing" << std::endl;
}