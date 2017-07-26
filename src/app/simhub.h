#ifndef __SIMHUB_H
#define __SIMHUB_H

#include <string>
#include <thread>

#include "elements/attributes/attribute.h"
#include "libs/plugins/common/queue/concurrent_queue.h"
#include "plugins/common/simhubdeviceplugin.h"

class ConfigManager; // forward reference

/**
 * Base of the simhub app controller logic
 *
 * - sets up a capture-less lambda that is called by a plugin instance
 *   (on a separate thread) when the plugin generates an event
 *
 * - the lambda callback then uses the final arg of the callback, a
 *   void * to 'this' that was passed to the plugin when it registered
 *   the callback stub, to call into the proper 'eventCallback' member
 */
class SimHubEventController
{
protected:
    static std::shared_ptr<SimHubEventController> _EventControllerInstance;

protected:
    SimHubEventController(void);

    void prepare3dEventCallback(SPHANDLE eventSource, void *eventData);
    void pokeyEventCallback(SPHANDLE eventSource, void *eventData);
    simplug_vtable loadPlugin(std::string dylibName, EnqueueEventHandler eventCallback);
    void terminate(void);
    void shutdownPlugin(simplug_vtable &pluginMethods);

    ConcurrentQueue<std::shared_ptr<Attribute>> _eventQueue;
    simplug_vtable _prepare3dMethods;
    simplug_vtable _pokeyMethods;
    ConfigManager *_configManager;

public:
    virtual ~SimHubEventController(void);

    void loadPrepare3dPlugin(void);
    void loadPokeyPlugin(void);

    bool deliverPokeyPluginValue(std::shared_ptr<Attribute> value);
    void setConfigManager(ConfigManager *configManager) { _configManager = configManager; };

    template <class F> void runEventLoop(F &&eventProcessorFunctor);

public:
    static void LoggerWrapper(const int category, const char *msg, ...);
    static std::shared_ptr<SimHubEventController> EventControllerInstance(void);
};

//! TODO - add perpetual and cancellable loop
// - currently just waits on the concurrent event queue
//   -> when another thread pushes an event on the queue, this thread
//      will awake and pop the event

template <class F> void SimHubEventController::runEventLoop(F &&eventProcessorFunctor)
{
    bool breakLoop = false;

    while (!breakLoop) {
        std::shared_ptr<Attribute> data = _eventQueue.pop();
        logger.log(LOG_INFO, "popped (%s: %s) off the concurrent event queue", data->_name.c_str(), data->getValueToString().c_str());
        breakLoop = !eventProcessorFunctor(data);
    }

    terminate();
}

#endif
