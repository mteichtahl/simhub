#include "simConfigManager.h"
#include <sys/stat.h>

/**
 *   @brief  Default  constructor for SimConfigManager
 *
 *   @return nothing
 */
SimConfigManager::SimConfigManager(libconfig::Config *config, std::string pluginDir)
{
    _config = config;
    _pluginDir = pluginDir;

    try {
        _simConfig = &_config->lookup("configuration.simulator")[0];
        if (!validateConfig()) {
            logger.log(LOG_ERROR, "[SimConfigManager] Unable to validate config.");
        }
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        logger.log(LOG_ERROR, "No %s set in config", nfex.what());
    }
}

/**
 *   @brief check if a file on the file system exists
 *
 *   @param  std::string A string representing the name of the file to check
 *
 *   @return bool true if file exists, otherwise false
 */
bool SimConfigManager::fileExists(std::string filename)
{
    return (filename.size() > 0 && access(filename.c_str(), 0) == 0);
}

/**
 *   @brief check if the simulator section of the configuration file is correct
 *
 *   @return bool true if configuration ok, otherwise false
 */
bool SimConfigManager::validateConfig(void)
{

    int hasError = false;

    if (!_simConfig) {
        logger.log(LOG_ERROR, "[SimConfigManager] Could not get simulator configuration");
        return RETURN_ERROR;
    }

    // iterate through the mandatory config fields and check they are present
    std::vector<std::string>::iterator it;

    for (it = _requiredSimulatorConfigurationFields.begin(); it < _requiredSimulatorConfigurationFields.end(); it++) {
        if (!_simConfig->exists(it->c_str())) {
            hasError++;
            logger.log(LOG_ERROR, "[SimConfigManager]  - mandatory field '%s' does not exist in simulator config", it->c_str());
        }
    }

    if (hasError) {
        logger.log(LOG_ERROR, "[SimConfigManager]  %d missing field(s) in simulator configuration", hasError);
        return RETURN_ERROR;
    }

    // check the plugin for the simulator is present
    _pluginName = _simConfig->lookup("type").c_str();

    if (!fileExists(_pluginDir + "/lib" + _pluginName + ".dylib")) {
        logger.log(LOG_ERROR, " - simulator plugin %s does not exist ", (_pluginDir + "/lib" + _pluginName + ".dylib").c_str());
        return RETURN_ERROR;
    }

    return RETURN_OK;
}
