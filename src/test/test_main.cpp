#include "test_logging.h"
#include <thread>
#include <gtest/gtest.h>

#include "plugins/simsource/simsource.h"
#include "concurrent_queue.h"

// -- these are examples, showing the general test syntax
 
TEST(SquareRootTest, PositiveNos) 
{ 
}
 
TEST(SquareRootTest, ZeroAndNegativeNos) 
{ 
}
                       
TEST(PluginsTest, BasicTest)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);
    
    int err = simplug_bootstrap("plugins/libsimplug_simsource.dylib", &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance);

        
        ConcurrentQueue<std::string> testEventQueue;

        // this callback will be called from the thread of the event
        // generator which is assumed to not be the thread of the for
        // loop below
        
        static std::function<void (SPHANDLE, void *)> testFnBounce = [&](SPHANDLE eventSource, void* eventData)
            {
                std::cout << "event handler called" << std::endl;
                testEventQueue.push("...event...");
            };

        // proxy the C style call through to the lambda above, which
        // manages the var capture
        
        auto testFn = [](SPHANDLE eventSource, void *eventData)
            {
                testFnBounce(eventSource, eventData);
            };
        
        pluginMethods.simplug_commence_eventing(pluginInstance, testFn);

        for (size_t i = 0; i < 10; i++) {
            std::string data = testEventQueue.pop();

            std::cout << "just popped: " << data << " off the concurrent event queue" << std::endl;
        }
        
        pluginMethods.simplug_cease_eventing(pluginInstance);
        pluginMethods.simplug_release(pluginInstance);
    }
}
 
int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
