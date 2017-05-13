#include "test_logging.h"
#include <gtest/gtest.h>
#include <thread>

#include "../common/configmanager/configmanager.h"
#include "concurrent_queue.h"
#include "libs/commandLine.h"
#include "log/clog.h"
#include "simsource.h"

TEST(PluginsTest, BasicTest)
{
    ConcurrentQueue<std::string> testEventQueue;

    // for (int i = 0; i < 10; i++) {
    //     // we will block here until there is something in the queue
    //     std::string data = testEventQueue.pop();
    //     std::cout << "just popped: " << data << " off the concurrent event queue" << std::endl;
    // }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    cmdline::parser cli;
    cli.add<std::string>("config", 'c', "config file", false, "config/config.cfg");
    cli.add<std::string>("logConfig", 'l', "log config file", false, "config/zlog.conf");

    cli.set_program_name("simhub");
    cli.footer("\n");

    logger.init(cli.get<std::string>("logConfig"));

    CConfigManager config(cli.get<std::string>("config"));

    return RUN_ALL_TESTS();
}
