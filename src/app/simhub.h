#ifndef __SIMHUB_H
#define __SIMHUB_H

#include <string>

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
    void loadPlugin(std::string dylibName, EnqueueEventHandler eventCallback);

    ConcurrentQueue<std::string> _eventQueue;

public:
    SimHubEventController(void);
    virtual ~SimHubEventController(void);

    void loadPrepare3dPlugin(void);
    void loadPokeyPlugin(void);
};

#endif
