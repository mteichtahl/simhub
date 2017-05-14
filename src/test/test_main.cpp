#include <thread>
#include <gtest/gtest.h>

#include "plugins/simsource/simsource.h"
#include "concurrent_queue.h"
#include "test_logging.h"

// -- these are examples, showing the general test syntax
 
TEST(SquareRootTest, PositiveNos) 
{ 
}
 
TEST(SquareRootTest, ZeroAndNegativeNos) 
{ 
}

/**
 * simple state management class used by the PluginTests 
 *
 * - sets up a capture-less lambda that is called by a plugin instance
 *   (on a separate thread) when the plugin generates an event
 *
 * - the lambda callback then uses the final arg of the callback, a
 *   void * to 'this' that was passed to the plugin when it registered
 *   the callback stub, to call into the proper 'eventCallback' member
 */
class EventConsumer
{
protected:
    void eventCallback(SPHANDLE eventSource, void *eventData);
    ConcurrentQueue<std::string> _testEventQueue;
    
public:
    void runConsumptionTest(void);
};

// this callback will be called from the thread of the event
// generator which is assumed to not be the thread of the for
// loop below

void EventConsumer::eventCallback(SPHANDLE eventSource, void *eventData)
{
    std::cout << "event handler called" << std::endl;
    _testEventQueue.push("...event...");
}

void EventConsumer::runConsumptionTest(void)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);

    
    int err = simplug_bootstrap("plugins/libsimplug_simsource.dylib", &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance);

        // proxy the C style lambda call through to the member
        // function above
        
        auto testFn = [](SPHANDLE eventSource, void *eventData, void *arg) {
            static_cast<EventConsumer*>(arg)->eventCallback(eventSource, eventData);
        };
        
        pluginMethods.simplug_commence_eventing(pluginInstance, testFn, this);

        for (size_t i = 0; i < 9; i++) {
            std::string data = _testEventQueue.pop();

            std::cout << "just popped: " << data << " off the concurrent event queue" << std::endl;
        }
        
        pluginMethods.simplug_cease_eventing(pluginInstance);
        pluginMethods.simplug_release(pluginInstance);
    }
}

TEST(PluginsTest, BasicTest)
{
    EventConsumer consumer;
    consumer.runConsumptionTest();
}
 
int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
