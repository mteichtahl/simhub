#include <assert.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "../common/simHubDevicePlugin.h"

class PluginStateManager
{
protected:
    virtual void runTestEventLoop(void);
    EnqueueEventHandler _enqueueCallback;
    std::thread _testEventThread;
    void *_callbackArg;

public:
    PluginStateManager(void);
    virtual ~PluginStateManager(void);

    virtual int bindConfigValues(char *group_name, ConfigEntry **values, int count);
    virtual int preflightComplete(void);
    virtual void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    virtual void ceaseEventing(void);
};

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

// -- public C FFI

extern "C" {
int simplug_init(SPHANDLE *plugin_instance)
{
    *plugin_instance = new PluginStateManager();
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
