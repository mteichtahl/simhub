#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "configManager/CConfigManager.h"
#include "libs/commandLine.h" // https://github.com/tanakh/cmdline
#include "log/CLog.h"

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

    return 0;
}
