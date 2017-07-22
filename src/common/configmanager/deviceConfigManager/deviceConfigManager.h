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
#include "../simConfigManager/simConfigManager.h"
#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>
#include <sys/stat.h>
#include <vector>

#ifndef RETURN_OK
#define RETURN_OK 1
#endif
#ifndef RETURN_ERROR
#define RETURN_ERROR -1
#endif

class DeviceConfigManager
{
protected:
    bool isValidConfig;
    libconfig::Config *_config; //< reference to config owned by other class
    libconfig::Setting *_deviceConfig; //< internal reference pointer
    std::string _pluginDir;
    std::map<std::string, std::shared_ptr<Device>> _device;
    std::shared_ptr<SimConfigManager> _simConfigManager;

public:
    DeviceConfigManager(libconfig::Config *config,
                        SimHubEventController *simhubController,
                        std::string pluginDir = "./plugins");
    ~DeviceConfigManager();
};

#endif
