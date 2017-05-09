#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../common/configmanager/configmanager.h"
#include "../common/elements/sources/source.h"
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

    // const libconfig::Setting *simConfig = config.getSimulatorConfig();

    // std::string ip = simConfig->lookup("ipAddress");

    Source el("element", "desc");

    Attribute attr;
    attr._name = "at1name";
    attr._description = "lkfjdslfjkds";
    attr._type = FLOAT_ATTRIBUTE;
    attr.setValue<float>(1.223);

    el.addAttribute(attr);

    Attribute at = el.getAttribute("at1name");

    printf("----> %0.5f\n", at.getValue<float>());
    printf("----> %s\n", at.getValueToString<float>().c_str());
    printf("----> %s\n", at.timestampString().c_str());

    return 0;
}
