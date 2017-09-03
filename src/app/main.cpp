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

// TODO: handle SIGHUP for settings reload
void sigint_handler(int sigid)
{
    if (sigid == SIGINT) {
        // tell app event loop to end on control+c
        logger.log(LOG_INFO, "Shutting down simhub, this may take a couple seconds...");
        SimHubEventController::EventControllerInstance()->ceaseEventLoop();
    }
    else if (sigid == SIGHUP) {
    }
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = sigint_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGHUP, &act, NULL);

    cmdline::parser cli;
    configureCli(&cli);
    cli.parse_check(argc, argv);

    logger.init(cli.get<std::string>("logConfig"));

    ConfigManager config(cli.get<std::string>("config"));
    std::shared_ptr<SimHubEventController> simhubController = SimHubEventController::EventControllerInstance();

    ///! If the AWS SDK is being used then read in the polly cli and load up polly

    ///! initialise the configuration
    if (!config.init(simhubController)) {
        logger.log(LOG_ERROR, "Could not initialise configuration");
        exit(1);
    }

#if defined(_AWS_SDK)
    simhubController->enablePolly();
    simhubController->enableKinesis();
#endif

    if (simhubController->loadPokeyPlugin()) {
        if (simhubController->loadPrepare3dPlugin()) {

            // kick off the simhub envent loop

            simhubController->runEventLoop([=](std::shared_ptr<Attribute> value) {
                std::cout << "desc: " << value->description() << ", units: " << value->units() << std::endl;
                bool deliveryResult = simhubController->deliverValue(value);

#if defined(_AWS_SDK)
                simhubController->deliverKinesisValue(value);
#endif
                return deliveryResult;
            });
        }
        else {
            logger.log(LOG_ERROR, "error loading prepare3d plugin");
        }
    }
    else {
        logger.log(LOG_ERROR, "Could not pokey plugin");
    }

    return 0;
}
