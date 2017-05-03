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

    Source el("element", "desc");

    Element::attribute_t attr;
    attr.name = "at1name";
    attr.description = "lkfjdslfjkds";
    attr.type = Element::eAttributeTypes::STRING_ATTRIBUTE;
    attr.defaultValue = "";
    attr.value = "";

    el.addAttribute(attr);
    el.addAttribute(attr);

    Element::attribute_t poo = el.getAttribute("at1name");
    printf("%s", poo.name.c_str());

    return 0;
}
