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

#include "log/clog.h"

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

    bool fileExists(std::string filename);

public:
    CConfigManager(std::string);
    std::string getConfigFilename(void);
    int init(void);
    std::string version();
    std::string name();
};

#endif
