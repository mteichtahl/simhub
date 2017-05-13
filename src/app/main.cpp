#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../common/configmanager/configmanager.h"
#include "../common/elements/sources/source.h"
#include "concurrent_queue.h" // https://github.com/juanchopanza/cppblog/tree/master/Concurrency/Queue
#include "libs/commandLine.h" // https://github.com/tanakh/cmdline
#include "log/clog.h"

void configureCli(cmdline::parser *cli)
{
    cli->add<std::string>("config", 'c', "config file", false, "config/config.cfg");
    cli->add<std::string>("logConfig", 'l', "log config file", false, "config/zlog.conf");

    cli->set_program_name("simhub");
    cli->footer("\n");
}

int main(int argc, char *argv[])
{
    cmdline::parser cli;
    configureCli(&cli);
    cli.parse_check(argc, argv);

    logger.init(cli.get<std::string>("logConfig"));

    CConfigManager config(cli.get<std::string>("config"));

    if (!config.init()) {
        logger.log(LOG_ERROR, "Could not initialise configuration");
        exit(1);
    }

    return 0;
}
