#ifndef __DEVICECONFIGMANAGER_H
#define __DEVICECONFIGMANAGER_H

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

#include "../../device/device.h"
#include "../../log/clog.h"
#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>
#include <sys/stat.h>
#include <vector>

#define RETURN_OK 1
#define RETURN_ERROR 0

class DeviceConfigManager
{
protected:
    bool isValidConfig;
    libconfig::Config *_config;
    libconfig::Setting *_deviceConfig;
    std::string _pluginDir;
    std::map<std::string, Device *> _device;

public:
    DeviceConfigManager(libconfig::Config *config, std::string pluginDir = "./plugins");
    ~DeviceConfigManager();
};

#endif
