#include "configmanager.h"

/**
 *   @brief  Default  constructor for CConfigManager
 *
 *   @return nothing
 */
CConfigManager::CConfigManager(std::string filename)
{
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
CConfigManager::~CConfigManager()
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
bool CConfigManager::fileExists(std::string filename)
{
    return (filename.size() > 0 && access(filename.c_str(), 0) == 0);
}

/**
 *   @brief check if a directory on the file system exists
 *
 *   @param  std::string A string representing the name of the directory to check
 *
 *   @return bool true if directory exists, otherwise false
 */
bool CConfigManager::dirExists(std::string dirname)
{
    if (dirname.size() > 0 && access(dirname.c_str(), 0) == 0) {
        struct stat status;
        stat(dirname.c_str(), &status);
        if (status.st_mode & S_IFDIR) {
            return true;
        }
    }
    return false;
}

std::string CConfigManager::getConfigFilename(void)
{
    return _configFilename;
}

int CConfigManager::init(void)
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

    logger.log(LOG_INFO, "Loading configuration file: %s - %s (v%s) (v%d.%d.%d)", _configFilename.c_str(),
        name().c_str(), version().c_str(), LIBCONFIGXX_VER_MAJOR, LIBCONFIGXX_VER_MINOR, LIBCONFIGXX_VER_REVISION);

    _root = &_config.getRoot();

    if (isValidSimConfiguration()) {
        return RETURN_OK;
    }
    else {
        return RETURN_ERROR;
    }
    return RETURN_ERROR;
}

bool CConfigManager::isValidSimConfiguration(void)
{
    const libconfig::Setting *simConfig = getSimulatorConfig();
    int hasError = false;

    if (!simConfig) {
        logger.log(LOG_ERROR, "Could not get simulator configuration");
        return false;
    }

    std::vector<std::string>::iterator it;

    for (it = _requiredSimulatorConfigurationFields.begin(); it < _requiredSimulatorConfigurationFields.end(); it++) {
        if (!simConfig->exists(it->c_str())) {
            hasError++;
            logger.log(LOG_ERROR, " - mandatory field '%s' does not exist in simulator config", it->c_str());
        }
    }

    if (hasError) {
        logger.log(LOG_ERROR, "%d missing field(s) in simulator configuration", hasError);
        return RETURN_ERROR;
    }
    else {
        return RETURN_OK;
    }
}

const libconfig::Setting *CConfigManager::getSimulatorConfig(void)
{
    try {
        libconfig::Setting &simulatorConfig = _config.lookup("configuration.simulator");
        return &simulatorConfig[0];
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        logger.log(LOG_ERROR, "No %s set in config", nfex.what());
        return NULL;
    }
}

std::string CConfigManager::version(void)
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

std::string CConfigManager::pluginDir(void)
{
    if (_pluginDir.empty()) {
        try {
            _pluginDir = (const char *)_config.lookup("pluginDir");
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "No plugin directory set in config");
        }
    }

    return _pluginDir;
}

std::string CConfigManager::name(void)
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

