#include <assert.h>

#include "log/clog.h"
#include "simhub.h"

// TODO: FIX EVERYTHING

SimHubEventController::SimHubEventController(void)
{
    logger.log(LOG_INFO, "Starting event controller");
}

SimHubEventController::~SimHubEventController(void)
{
}

// this callback will be called from the thread of the event
// generator which is assumed to not be the thread of the for
// loop below

void SimHubEventController::prepare3dEventCallback(SPHANDLE eventSource, void *eventData)
{
    logger.log(LOG_INFO, "prepare3dEventCallback handler called");
    _eventQueue.push("...event...");
}

void SimHubEventController::pokeyEventCallback(SPHANDLE eventSource, void *eventData)
{
    logger.log(LOG_INFO, "event handler called");
    _eventQueue.push("...event...");
}

void SimHubEventController::loadPlugin(std::string dylibName, EnqueueEventHandler eventCallback)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);

    // TODO: use correct path
    std::string fullPath("plugins/");
    fullPath += dylibName;

    int err = simplug_bootstrap(fullPath.c_str(), &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance);

        if (pluginMethods.simplug_preflight_complete(pluginInstance) == 0) {
            // proxy the C style lambda call through to the member
            // function above

            pluginMethods.simplug_commence_eventing(pluginInstance, eventCallback, this);

            for (size_t i = 0; i < 9; i++) {
                std::string data = _eventQueue.pop();

                std::cout << "just popped: " << data << " off the concurrent event queue" << std::endl;
            }

            pluginMethods.simplug_cease_eventing(pluginInstance);
            pluginMethods.simplug_release(pluginInstance);
        }
        else {
            assert(false);
        }
    }
    else {
        assert(false);
    }
}

void SimHubEventController::loadPrepare3dPlugin(void)
{
    auto prepare3dCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->prepare3dEventCallback(eventSource, eventData); };
    loadPlugin("libprepare3d.dylib", prepare3dCallback);
}

void SimHubEventController::loadPokeyPlugin(void)
{
    auto pokeyCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->pokeyEventCallback(eventSource, eventData); };
    loadPlugin("libpokey.dylib", pokeyCallback);
}
