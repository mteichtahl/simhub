#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "configManager/CConfigManager.h"
#include "libs/commandLine.h" // https://github.com/tanakh/cmdline
#include "log/CLog.h"

using namespace std;

void configureCli(cmdline::parser* cli) {
    cli->add<string>("config", 'c', "config file", false, "config/config.cfg");
    cli->add<string>("logConfig", 'l', "log config file", false, "config/zlog.conf");

    cli->set_program_name("simhub");
    cli->footer("\n");
}

int main(int argc, char* argv[]) {
    cmdline::parser cli;
    configureCli(&cli);
    cli.parse_check(argc, argv);

    logger.init(cli.get<string>("logConfig"));

    CConfigManager config(cli.get<string>("config"));

    return 0;
}
