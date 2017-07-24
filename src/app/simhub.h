#ifndef __SIMHUBEVENT_H
#define __SIMHUBEVENT_H

#include <string>
#include <thread>

#include "elements/attributes/attribute.h"
#include "libs/plugins/common/queue/concurrent_queue.h"
#include "plugins/common/simhubdeviceplugin.h"

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
    void prepare3dEventCallback(SPHANDLE eventSource, void *eventData);
    void pokeyEventCallback(SPHANDLE eventSource, void *eventData);
    simplug_vtable loadPlugin(std::string dylibName, EnqueueEventHandler eventCallback);
    void shutdownPlugin(simplug_vtable &pluginMethods);

    ConcurrentQueue<std::shared_ptr<Attribute>> _eventQueue;
    simplug_vtable _prepare3dMethods;
    simplug_vtable _pokeyMethods;

    static SimHubEventController *EventControllerInstance(void);
    static SimHubEventController *_EventControllerInstance;

public:
    SimHubEventController(void);
    virtual ~SimHubEventController(void);

    void loadPrepare3dPlugin(void);
    void loadPokeyPlugin(void);
    void runEventLoop(void);
    void terminate(void);

    static void LoggerWrapper(const int category, const char *msg, ...);
};

#endif
