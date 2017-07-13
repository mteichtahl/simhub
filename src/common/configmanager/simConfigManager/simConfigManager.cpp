#include <sys/stat.h>
#include <assert.h>

#include "simConfigManager.h"

/**
 *   @brief  Default  constructor for SimConfigManager
 *
 *   @return nothing
 */
SimConfigManager::SimConfigManager(libconfig::Setting *setting, SimHubEventController *simhubController, std::string pluginDir)
    : _simConfig(setting)
    , _simhubController(simhubController)
    , _pluginDir(pluginDir)
{
    if (!validateConfig()) {
        throw std::runtime_error("[SimConfigManager] Unable to validate config.");
    }

    _simhubController->loadPrepare3dPlugin();
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
        throw std::logic_error("[SimConfigManager] Could not get simulator configuration");
        return RETURN_ERROR;
    }

    // iterate through the mandatory config fields and check they are present
    std::vector<std::string>::iterator it;

    for (it = _requiredSimulatorConfigurationFields.begin(); it < _requiredSimulatorConfigurationFields.end(); it++) {
        if (!_simConfig->exists(it->c_str())) {
            hasError++;
            logger.log(LOG_ERROR, "[SimConfigManager] requiredfield '%s' does not exist in simulator config", it->c_str());
        }
    }

    if (hasError) {
        logger.log(LOG_ERROR, "[SimConfigManager] %d missing field(s) in simulator configuration", hasError);
        return RETURN_ERROR;
    }

    // check the plugin for the simulator is present
    _pluginName = _simConfig->lookup("type").c_str();

    if (!fileExists(_pluginDir + "/lib" + _pluginName + ".dylib")) {
        std::string msg = "[SimConfigManager] plugin does not exist " + _pluginDir + "/lib" + _pluginName + ".dylib";
        throw std::logic_error(msg.c_str());
    }

    return RETURN_OK;
}

const std::string SimConfigManager::IPAddress(void)
{
    return _simConfig->lookup("ipAddress").c_str();
}

const int SimConfigManager::port(void)
{
    return _simConfig->lookup("port");
}

const std::string SimConfigManager::type(void)
{
    return _simConfig->lookup("type").c_str();
}
