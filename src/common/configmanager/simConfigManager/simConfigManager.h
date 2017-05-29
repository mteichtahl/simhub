#ifndef __SIMCONFIGMANAGER_H
#define __SIMCONFIGMANAGER_H

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

#include "../../log/clog.h"
#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>
#include <sys/stat.h>
#include <vector>

#define RETURN_OK 1
#define RETURN_ERROR 0

class SimConfigManager
{
protected:
    bool isValidConfig;
    std::vector<std::string> _requiredSimulatorConfigurationFields = { "ipAddress", "port", "type" };
    libconfig::Config *_config;
    libconfig::Setting *_simConfig;
    std::string _pluginDir;
    std::string _pluginName;

public:
    SimConfigManager(libconfig::Config *config, std::string pluginDir = "./plugins");
    const libconfig::Setting *getConfig(void);
    bool validateConfig(void);
    bool fileExists(std::string filename);
    const std::string getIPAddress();
    const int getPort();
    const std::string getType();
};

#endif
