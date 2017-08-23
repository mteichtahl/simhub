#ifndef __CCONFIGMANAGER_H
#define __CCONFIGMANAGER_H

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

#include <exception>
#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>
#include <vector>

#if defined(_AWS_SDK)
#include "aws/aws.h"
#endif

#include "log/clog.h"
#include "mappingConfigManager/mappingConfigManager.h"
#include "simhub.h"

#ifndef RETURN_OK
#define RETURN_OK 1
#endif
#ifndef RETURN_ERROR
#define RETURN_ERROR -1
#endif

/**
 * Base class for all pin based classes
 **/
class ConfigManager
{
protected:
    libconfig::Config _config;
    std::string _configFilename;
    std::string _configFileVersion;
    std::string _configName;

    std::string _mappingConfigFilename;
    std::shared_ptr<MappingConfigManager> _mappingConfigManager;

    libconfig::Config _prepare3dConfig;
    std::string _prepare3dConfigurationFilename;

    libconfig::Config _pokeyConfig;
    std::string _pokeyConfigurationFilename;

    libconfig::Setting *_root;

    bool fileExists(std::string filename);

public:
    ConfigManager(std::string);
    virtual ~ConfigManager(void);

    int init(std::shared_ptr<SimHubEventController> simhubController);
    std::string configFilename(void);
    std::string mappingConfigFilename(void);
    std::string loadPrepare3DConfiguration(void);
    std::string loadPokeyConfiguration(void);
    std::string version(void);
    std::string name(void);
    std::shared_ptr<MappingConfigManager> mapManager(void);
    libconfig::Config *config() { return &_config; }
};

#endif
