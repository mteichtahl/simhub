#include <gtest/gtest.h>

#include "plugins/simsource/simsource.h"

// -- these are examples, showing the general test syntax
 
TEST(SquareRootTest, PositiveNos) 
{ 
}
 
TEST(SquareRootTest, ZeroAndNegativeNos) 
{ 
}

extern "C" void TestEnqueueEventHandler(void *eventData)
{
    std::cout << "event handler called" << std::endl;
}

TEST(PluginsTest, BasicTest)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);
    
    int err = simplug_bootstrap("plugins/libsimplug_simsource.so", &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance);
        pluginMethods.simplug_commence_eventing(pluginInstance, &TestEnqueueEventHandler);
        pluginMethods.simplug_cease_eventing(pluginInstance);
        pluginMethods.simplug_release(pluginInstance);
    }
}
 
int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
