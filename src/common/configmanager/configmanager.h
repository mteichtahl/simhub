#ifndef __CCONFIGMANAGER_H
#define __CCONFIGMANAGER_H

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>
#include <vector>

#include "log/clog.h"

#define RETURN_OK 1
#define RETURN_ERROR -1

/**
 * Base class for all pin based classes
 **/
class CConfigManager
{
protected:
    libconfig::Config _config;
    std::string _configFilename;
    std::string _configFileVersion;
    std::string _configName;
    std::string _pluginDir;
    libconfig::Setting *_root;

    bool fileExists(std::string filename);
    bool isValidSimConfiguration(void);

    std::vector<std::string> _requiredSimulatorConfigurationFields = { "ipAddress", "port", "type" };
    std::vector<std::string> _requiredDeviceConfigurationFields = { "serialNumber", "uid", "name", "dhcp" };

public:
    CConfigManager(std::string);
    ~CConfigManager();
    std::string getConfigFilename(void);
    int init(void);
    std::string version(void);
    std::string name(void);
    std::string pluginDir(void);

    const libconfig::Setting *getSimulatorConfig(void);
};

#endif
