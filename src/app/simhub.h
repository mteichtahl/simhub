#ifndef __SIMHUB_H
#define __SIMHUB_H

#include <atomic>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <sstream>
#include <cpprest/http_listener.h>

#include "plugins/common/utils.h"
#include "elements/attributes/attribute.h"
#include "plugins/common/simhubdeviceplugin.h"
#include "common/support/threadmanager.h"
#include "queue/concurrent_queue.h"

#if defined(_AWS_SDK)
#include "aws/aws.h"
#include "common/support/threadmanager.h"
#endif

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

typedef std::pair<std::chrono::milliseconds, std::shared_ptr<Attribute>> SustainMapEntry;

class SimHubEventController
{
protected:
    static std::shared_ptr<SimHubEventController> _EventControllerInstance;

protected:
    SimHubEventController(void);

    void prepare3dEventCallback(SPHANDLE eventSource, void *eventData);
    void pokeyEventCallback(SPHANDLE eventSource, void *eventData);
    simplug_vtable loadPlugin(std::string dylibName, libconfig::Config *pluginConfigs, EnqueueEventHandler eventCallback);
    void terminate(void);
    void shutdownPlugin(simplug_vtable &pluginMethods);
#if defined(_AWS_SDK)
    void startSustainThread(void);
    void ceaseSustainThread(void);
#endif

    ConcurrentQueue<std::shared_ptr<Attribute>> _eventQueue;
    simplug_vtable _prepare3dMethods;
    simplug_vtable _pokeyMethods;
    ConfigManager *_configManager;

#if defined(_AWS_SDK)
    CancelableThreadManager _sustainThreadManager;
    std::map<std::string, SustainMapEntry> _sustainValues;
    std::mutex _sustainValuesMutex;
#endif

    bool _running;

    // -- temp solution to plugin device configuration conundrum
    libconfig::Config *_pokeyDeviceConfig;
    libconfig::Config *_prepare3dDeviceConfig;

    //! implements configuration server
    std::shared_ptr<web::http::experimental::listener::http_listener> _configurationHTTPListener;
    std::string _httpListenAddress;
    size_t _httpListenPort;
    virtual void httpGETConfigurationHandler(web::http::http_request request);
    virtual void startHTTPListener(void);

public:
    virtual ~SimHubEventController(void);
    bool loadPrepare3dPlugin(void);
    bool loadPokeyPlugin(void);
    bool deliverValue(std::shared_ptr<Attribute> value);
    void setConfigManager(ConfigManager *configManager);

    // -- temp solution to plugin device configuration conundrum
    void setPrepare3dConfig(libconfig::Config *prepare3dConfig)
    {
        assert(prepare3dConfig != NULL);
        _prepare3dDeviceConfig = prepare3dConfig;
    };

    void setPokeyConfig(libconfig::Config *pokeyConfig)
    {
        assert(pokeyConfig != NULL);
        _pokeyDeviceConfig = pokeyConfig;
    };

    template <class F> void runEventLoop(F &&eventProcessorFunctor);

    void ceaseEventLoop(void);

#if defined(_AWS_SDK)
    AWS _awsHelper;

    void enablePolly(void);
    void enableKinesis(void);
    void deliverKinesisValue(std::shared_ptr<Attribute> value);
#endif

public:
    static void LoggerWrapper(const int category, const char *msg, ...);
    static std::shared_ptr<SimHubEventController> EventControllerInstance(void);
    static void DestroyEventControllerInstance(void);
};

//! TODO - add perpetual and cancelable loop
// - currently just waits on the concurrent event queue
//   -> when another thread pushes an event on the queue, this thread
//      will awake and pop the event

template <class F> void SimHubEventController::runEventLoop(F &&eventProcessorFunctor)
{
    bool breakLoop = false;

    _running = true;

#if defined(_AWS_SDK)
    startSustainThread();
#endif

    startHTTPListener();

    while (!breakLoop) {
        try {
            std::shared_ptr<Attribute> data = _eventQueue.pop();
            breakLoop = !eventProcessorFunctor(data);
        }
        catch (ConcurrentQueueInterrupted &queueException) {
            breakLoop = true;
        }
    }

    terminate();
}

#endif
