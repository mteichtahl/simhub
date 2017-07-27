#include "deviceConfigManager.h"
#include <sys/stat.h>

/**
 *   @brief  Default  constructor for SimConfigManager
 *
 *   @return nothing
 */
DeviceConfigManager::DeviceConfigManager(libconfig::Config *config,
                                         std::shared_ptr<SimHubEventController> simhubController,
                                         std::string pluginDir)
    : _config(config)
    , _pluginDir(pluginDir)
{

    Device *newDevice;

    _deviceConfig  = &_config->lookup("configuration.devices");
    logger.log(LOG_INFO, "Found %d devices", _deviceConfig->getLength());

    for (int i = 0; i <= _deviceConfig->getLength() - 1; i++) {
        libconfig::Setting *tmpDeviceConfig = &_config->lookup("configuration.devices")[i];
        std::string type;
        std::string id;

        try {
            type = tmpDeviceConfig->lookup("type").c_str();

            if (type == PREPARE3D) {
                logger.log(LOG_INFO, " - Creating %s simulator device", type.c_str());
                try {
                    _simConfigManager.reset(new SimConfigManager(tmpDeviceConfig, simhubController));
                    continue;
                }
                catch (libconfig::SettingNotFoundException &nfex) {
                    logger.log(LOG_ERROR, "No simulator section set in config [%s]", nfex.what());
                    continue;
                }
                catch (std::logic_error &e) {
                    logger.log(LOG_ERROR, "%s", e.what());
                    continue;
                }
            }
            id = tmpDeviceConfig->lookup("id").c_str();
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
            continue;
        }

        _device.emplace(id, std::make_shared<Device>(type, id, tmpDeviceConfig));
    }
}

DeviceConfigManager::~DeviceConfigManager()
{
    if (_device.size()) {
        _device.erase(_device.begin(), _device.end());
    }
}
