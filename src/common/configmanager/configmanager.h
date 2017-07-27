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

#include "deviceConfigManager/deviceConfigManager.h"
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
    libconfig::Setting *_root;
    std::shared_ptr<DeviceConfigManager> _deviceConfigManager;
    std::shared_ptr<MappingConfigManager> _mappingConfigManager;

    bool fileExists(std::string filename);

public:
    ConfigManager(std::string);
    virtual ~ConfigManager(void);

    std::string getConfigFilename(void);
    std::string getMappingConfigFilename(void);
    int init(std::shared_ptr<SimHubEventController> simhubController);
    std::string version(void);
    std::string name(void);
    std::shared_ptr<MappingConfigManager> mapManager(void);
};

#endif
