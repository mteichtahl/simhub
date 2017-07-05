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

#include "aws/aws.h"
#include "deviceConfigManager/deviceConfigManager.h"
#include "log/clog.h"
#include "mappingConfigManager/mappingConfigManager.h"

#ifndef RETURN_OK
#define RETURN_OK 1
#endif
#ifndef RETURN_ERROR
#define RETURN_ERROR -1
#endif

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
    std::string _mappingConfigFilename;
    libconfig::Setting *_root;
    DeviceConfigManager *_deviceConfigManager;
    MappingConfigManager *mappingConfigManager;

    bool fileExists(std::string filename);

public:
    CConfigManager(std::string);
    ~CConfigManager();

    std::string getConfigFilename(void);
    std::string getMappingConfigFilename(void);
    int init(void);
    std::string version(void);
    std::string name(void);
};

#endif
