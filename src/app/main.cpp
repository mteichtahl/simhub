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

    // Source el("element", "desc");

    // Attribute attr;
    // attr._name = "at1name";
    // attr._description = "lkfjdslfjkds";
    // attr._value = "1";
    // attr._type = eAttribute_t::STRING_ATTRIBUTE;

    // el.addAttribute(attr);

    // Attribute at = el.getAttribute("at1name");

    // logger.log(LOG_INFO, at.toString());
    // logger.log(LOG_INFO, "%d", el.attributeCount());

    return 0;
}
