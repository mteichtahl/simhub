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

/**
    Configure the main CLI interdace

    @param cmdline::parser pointer - command line parameters passed in by user

*/
void configureCli(cmdline::parser *cli)
{
    cli->add<std::string>("config", 'c', "config file", false, "config/config.cfg");
    cli->add<std::string>("logConfig", 'l', "log config file", false, "config/zlog.conf");

///! If the AWS SDK is being used then allow Polly as a CLI option
#if defined(_AWS_SDK)
    cli->add<bool>("polly", 'p', "Use Amazon Polly", false, true);
    cli->add<bool>("kinesis", 'k', "Use Amazon Kinesis", false, true);
#endif

    cli->set_program_name("simhub");
    cli->footer("\n");
}

void sigint_handler(int sigid)
{
    // tell app event loop to end on control+c
    std::cout << "shutting down..." << std::endl;
    SimHubEventController::EventControllerInstance()->ceaseEventLoop();
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = sigint_handler;
    sigaction(SIGINT, &act, NULL);

    cmdline::parser cli;
    configureCli(&cli);
    cli.parse_check(argc, argv);

    logger.init(cli.get<std::string>("logConfig"));

    ConfigManager config(cli.get<std::string>("config"));
    std::shared_ptr<SimHubEventController> simhubController = SimHubEventController::EventControllerInstance();

///! If the AWS SDK is being used then read in the polly cli and load up polly
#if defined(_AWS_SDK)
    awsHelper.init();
    if (cli.get<bool>("polly")) {
        awsHelper.initPolly();
    }
    if (cli.get<bool>("kinesis")) {
        awsHelper.initKinesis();
    }
#endif
    ///! initialise the configuration
    if (!config.init(simhubController)) {
        logger.log(LOG_ERROR, "Could not initialise configuration");
        exit(1);
    }

#if defined(_AWS_SDK)
    awsHelper.polly()->say("Loading plug in sub system");
#endif

    simhubController->loadPokeyPlugin(); ///< load the pokey plugin
    simhubController->loadPrepare3dPlugin(); ///< load the prepare3d plugin

#if defined(_AWS_SDK)
    awsHelper.polly()->say("Simulator is ready.");
#endif

    ///! kick off the simhub envent loop
    simhubController->runEventLoop([=](std::shared_ptr<Attribute> value) {
        bool deliveryResult = simhubController->deliverValue(value);

#if defined(_AWS_SDK)
        std::string name = value->name();
        std::string val = value->getValueToString();
        std::string ts = value->getTimestampAsString();

        // {s:"a",t:"b",v:"123", ts:121}
        std::stringstream ss;

        ss << "{s:\"" << name << "\", v:\"" << val << "\", ts: " << ts << "\"}";
        std::string dataString = ss.str();

        Aws::Utils::ByteBuffer data(dataString.length());

        for (int i = 0; i < dataString.length(); i++)
            data[i] = dataString[i];

        awsHelper.kinesis()->putRecord(data);
#endif

        // if (FinishEventLoop)
        //     deliveryResult = false;

        return deliveryResult;
    });

#if defined(_AWS_SDK)
    if (awsHelper.polly()->isJoinable())
        awsHelper.polly()->thread()->join();

    if (awsHelper.kinesis()->isJoinable())
        awsHelper.kinesis()->thread()->join();
#endif

    return 0;
}
