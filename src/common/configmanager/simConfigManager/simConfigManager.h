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
#define PREPARE3D "prepare3d"

#include "simhub.h"

class SimConfigManager
{
protected:
    std::vector<std::string> _requiredSimulatorConfigurationFields = { "ipAddress", "port", "type" };

    bool isValidConfig;
    libconfig::Setting *_simConfig;
    std::string _pluginDir;
    std::string _pluginName;
    SimHubEventController *_simhubController;

public:
    SimConfigManager(libconfig::Setting *config, SimHubEventController *simhubController, std::string pluginDir = "./plugins");
    const libconfig::Setting *config(void);
    bool validateConfig(void);
    bool fileExists(std::string filename);
    const std::string IPAddress(void);
    const int port(void);
    const std::string type(void);
};

#endif
