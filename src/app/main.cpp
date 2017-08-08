#include <condition_variable>
#include <iostream>
#include <map>
#include <signal.h>
#include <string>
#include <thread>
#include <vector>

#if defined(_AWS_SDK)
#include "aws/aws.h"
#endif

#include "common/configmanager/configmanager.h"
#include "common/elements/sources/source.h"
#include "libs/commandLine.h" // https://github.com/tanakh/cmdline
#include "log/clog.h"
#include "plugins/common/simhubdeviceplugin.h"
#include "simhub.h"

void configureCli(cmdline::parser *cli)
{
    cli->add<std::string>("config", 'c', "config file", false, "config/config.cfg");
    cli->add<std::string>("logConfig", 'l', "log config file", false, "config/zlog.conf");

#if defined(_AWS_SDK)
    cli->add<bool>("polly", 'p', "Use Amazon Polly", false, true);
#endif

    cli->set_program_name("simhub");
    cli->footer("\n");
}

int main(int argc, char *argv[])
{
    cmdline::parser cli;
    configureCli(&cli);
    cli.parse_check(argc, argv);

    logger.init(cli.get<std::string>("logConfig"));

    ConfigManager config(cli.get<std::string>("config"));
    std::shared_ptr<SimHubEventController> simhubController = SimHubEventController::EventControllerInstance();

#if defined(_AWS_SDK)
    awsHelper.init();
    if (cli.get<bool>("polly")) {
        awsHelper.initPolly();
    }
#endif

    if (!config.init(simhubController)) {
        logger.log(LOG_ERROR, "Could not initialise configuration");
        exit(1);
    }

    simhubController->loadPokeyPlugin();
    simhubController->loadPrepare3dPlugin();

    simhubController->runEventLoop([=](std::shared_ptr<Attribute> value) {
        static size_t counter = 0;

        bool deliveryResult = simhubController->deliverPokeyPluginValue(value);

        // demonstrate loop control

        if (counter++ == 10000)
            deliveryResult = false;

        return deliveryResult;
    });

#if defined(_AWS_SDK)
    awsHelper.polly()->say("system ready %d %s", 1, "test");
#endif

#if defined(_AWS_SDK)
    if (awsHelper.polly()->isJoinable())
        awsHelper.polly()->thread()->join();
#endif

    return 0;
}
