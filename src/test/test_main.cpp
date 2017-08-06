#include "test_logging.h"
#include <gtest/gtest.h>
#include <thread>

#include "plugins/common/queue/concurrent_queue.h"
#include "plugins/common/simhubdeviceplugin.h"
#include "simhub.h"

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
    GenericTLV *data = (GenericTLV *)eventData;

    if (data->type == CONFIG_FLOAT)
        logger.log(LOG_INFO, "[SimHubEventController] %s %2.6f", data->name, data->value.float_value);

    if (data->type == CONFIG_STRING)
        logger.log(LOG_INFO, "[SimHubEventController] %s %s", data->name, data->value.string_value);

    if (data->type == CONFIG_INT)
        logger.log(LOG_INFO, "[SimHubEventController] %s %i", data->name, data->value.int_value);

    if (data->type == CONFIG_BOOL)
        logger.log(LOG_INFO, "[SimHubEventController] %s %i", data->name, data->value.int_value);

    _testEventQueue.push("...event...");
}

void EventConsumer::runConsumptionTest(void)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);

    std::string plugin = "plugins/libprepare3d";
    plugin += LIB_EXT;

    int err = simplug_bootstrap(plugin.c_str(), &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance, SimHubEventController::LoggerWrapper);

        static const int TEST_VAL_COUNT = 3;
        GenericTLV *configValues[TEST_VAL_COUNT];
        configValues[0] = (GenericTLV *)calloc(1, sizeof(GenericTLV));
        configValues[0]->type = CONFIG_INT;
        configValues[0]->value.int_value = 42;
        configValues[0]->length = sizeof(configValues[0]->value.int_value);
        configValues[1] = (GenericTLV *)calloc(1, sizeof(GenericTLV));
        configValues[1]->type = CONFIG_STRING;
        configValues[1]->value.string_value = (char *)"42";
        configValues[1]->length = strlen(configValues[1]->value.string_value);
        configValues[2] = (GenericTLV *)calloc(1, sizeof(GenericTLV));
        configValues[2]->type = CONFIG_FLOAT;
        configValues[2]->value.float_value = 42.42;
        configValues[2]->length = sizeof(configValues[2]->value.float_value);

        // pluginMethods.simplug_bind_config_values(pluginInstance, (char *)"test_group", configValues, TEST_VAL_COUNT);

        if (pluginMethods.simplug_preflight_complete(pluginInstance) == 0) {
            // proxy the C style lambda call through to the member
            // function above

            auto testFn = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<EventConsumer *>(arg)->eventCallback(eventSource, eventData); };

            pluginMethods.simplug_commence_eventing(pluginInstance, testFn, this);

            for (size_t i = 0; i < 9; i++) {
                std::string data = _testEventQueue.pop();

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

TEST(PluginsTest, BasicTest)
{
    EventConsumer consumer;
    consumer.runConsumptionTest();
}

int main(int argc, char **argv)
{
    // ::testing::internal::CaptureStdout();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
