#include "configmanager.h"

/**
 *   @brief  Default  constructor for CConfigManager
 *
 *   @return nothing
 */
ConfigManager::ConfigManager(std::string filename)
{
	libconfig::Config test;
	
    if (fileExists(filename)) {
        _configFilename = filename;
    }
    else {
        logger.log(LOG_ERROR, "Config file %s does not exist", filename.c_str());
        throw std::runtime_error("Config I/O error - See log file");
    }
}

/**
 *   @brief  Default  destructor for CConfigManager
 *
 *   @return nothing
 */
ConfigManager::~ConfigManager()
{
    logger.log(LOG_INFO, "Closing configuration");
}

/**
 *   @brief check if a file on the file system exists
 *
 *   @param  std::string A string representing the name of the file to check
 *
 *   @return bool true if file exists, otherwise false
 */
bool ConfigManager::fileExists(std::string filename)
{
    return (filename.size() > 0 && access(filename.c_str(), 0) == 0);
}

std::string ConfigManager::getConfigFilename(void)
{
    return _configFilename;
}

std::string ConfigManager::getMappingConfigFilename(void)
{
    if (_mappingConfigFilename.empty()) {
        try {
            _mappingConfigFilename = (const char *)_config.lookup("mappingFile");
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "No mapping file set in config");
        }
    }

    return _mappingConfigFilename;
}

int ConfigManager::init(SimHubEventController *simhubController)
{
    // read the config file and handle any errors
    try {
        _config.readFile(_configFilename.c_str());
    }
    catch (const libconfig::FileIOException &fioex) {
        logger.log(LOG_ERROR, "Config file I/O error while reading file.");
        throw std::runtime_error("Config I/O error - See log file");
    }
    catch (const libconfig::ParseException &pex) {
        logger.log(LOG_ERROR, "Config file parse error at %s:%d  - %s", pex.getFile(), pex.getLine(), pex.getError());
        throw std::runtime_error("Config file parse error - See log file");
    }

    logger.log(LOG_INFO, "Loading configuration file: %s - %s (v%s) (v%d.%d.%d)", _configFilename.c_str(), name().c_str(), version().c_str(), LIBCONFIGXX_VER_MAJOR,
        LIBCONFIGXX_VER_MINOR, LIBCONFIGXX_VER_REVISION);

    _root = &_config.getRoot();

    /** load the device configuration mapping file **/
    try {
        _deviceConfigManager.reset(new DeviceConfigManager(&_config, simhubController));
    }
    catch (std::exception &e) {
        logger.log(LOG_ERROR, "%s", e.what());
        return RETURN_ERROR;
    }

    /** load the mapping configuration mapping file **/
    try {
        _mappingConfigManager.reset(new MappingConfigManager(getMappingConfigFilename()));
        _mappingConfigManager->init();
    }
    catch (std::exception &e) {
        logger.log(LOG_ERROR, "%s", e.what());
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

std::string ConfigManager::version(void)
{
    if (_configFileVersion.empty()) {
        try {
            _configFileVersion = (const char *)_config.lookup("version");
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "No version set in config");
        }
    }

    return _configFileVersion;
}

std::string ConfigManager::name(void)
{
    if (_configName.empty()) {
        try {
            _configName = (const char *)_config.lookup("name");
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "No name set in config");
        }
    }

    return _configName;
}
