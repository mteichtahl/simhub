#ifndef __MAPPINGCONFIGMANAGER_H
#define __MAPPINGCONFIGMANAGER_H

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

class MappingConfigManager
{
protected:
    bool isValidConfig;
    libconfig::Config _config;
    std::vector<std::string> _requiredConfigurationFields = { "source", "target" };
    libconfig::Setting *_mappingConfig;
    std::string _configFilename;
    std::string _mappingConfigFileVersion;
    std::string _configName;
    libconfig::Setting *_root;

public:
    MappingConfigManager(std::string);
    ~MappingConfigManager();
    const libconfig::Setting *getConfig(void);
    bool validateConfig(void);
    int init(void);
    bool fileExists(std::string filename);
    std::string getConfigFilename(void);
    std::string version(void);
};

#endif
