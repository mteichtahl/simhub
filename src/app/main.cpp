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

    simhubController->setConfigManager(&config);

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

    simhubController->runEventLoop([=](std::shared_ptr<Attribute> value) {
        static size_t counter = 0;

        bool deliveryResult = simhubController->deliverPokeyPluginValue(value);

        // demonstrate loop control

        if (counter++ == 100)
            deliveryResult = false;

        return deliveryResult;
    });

#if defined(_AWS_SDK)
    awsHelper.polly()->say("system ready %d %s", 1, "test");
#endif
// Source el("element", "desc");

// Attribute attr;
// attr._name = "at1name";
// attr._description = "lkfjdslfjkds";
// attr._type = FLOAT_ATTRIBUTE;
// attr.setValue<float>(1.223);

// el.addAttribute(attr);

// Attribute at = el.getAttribute("at1name");

// printf("----> %0.5f\n", at.getValue<float>());
// printf("----> %s\n", at.getValueToString<float>().c_str());
// printf("----> %s\n", at.timestampString().c_str());

#if defined(_AWS_SDK)
    if (awsHelper.polly()->isJoinable())
        awsHelper.polly()->thread()->join();
#endif

    return 0;
}
