#include "mappingConfigManager.h"

/**
 *   @brief  Default  constructor for CConfigManager
 *
 *   @return nothing
 */
MappingConfigManager::MappingConfigManager(std::string filename)
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
MappingConfigManager::~MappingConfigManager()
{
    logger.log(LOG_INFO, "Closing mapping configuration");
}

/**
 *   @brief check if a file on the file system exists
 *
 *   @param  std::string A string representing the name of the file to check
 *
 *   @return bool true if file exists, otherwise false
 */
bool MappingConfigManager::fileExists(std::string filename)
{
    return (filename.size() > 0 && access(filename.c_str(), 0) == 0);
}

std::string MappingConfigManager::getConfigFilename(void)
{
    return _configFilename;
}

int MappingConfigManager::init(void)
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

    logger.log(LOG_INFO, "Loading mapping configuration file: %s  (v%s)", _configFilename.c_str(), version().c_str());

    _root = &_config.getRoot();

    try {
        _mappingConfig = &_config.lookup("mapping");
        logger.log(LOG_INFO, " - Found %d mappings", _mappingConfig->getLength());

        for (int i = 0; i <= _mappingConfig->getLength() - 1; i++) {
            std::string source;
            std::string target;

            try {
                source = (const char *)(&(*_mappingConfig)[i])->lookup("source");
                target = (const char *)(&(*_mappingConfig)[i])->lookup("target");
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                logger.log(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
                continue;
            }
            catch (const libconfig::SettingTypeException &nfex) {
                logger.log(LOG_ERROR, "Setting type error for %s. Skipping....", nfex.getPath());
                continue;
            }

            std::pair<std::map<std::string, mapEntry>::iterator, bool> ret;
            auto pair = std::make_pair(source, target);
            ret = _mapping.insert(std::make_pair(source, pair));

            if (!ret.second) {
                logger.log(LOG_INFO, "  - skipping duplicate source %s ", source.c_str());
                continue;
            }
            else {
                logger.log(LOG_INFO, "  - adding %s -> %s", source.c_str(), target.c_str());
            }
        }
        logger.log(LOG_INFO, " - Added %d mappings", _mapping.size());
    }
    catch (std::exception &e) {
        logger.log(LOG_ERROR, "%s", e.what());
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

std::string MappingConfigManager::version(void)
{
    if (_mappingConfigFileVersion.empty()) {
        try {
            _mappingConfigFileVersion = (const char *)_config.lookup("version");
        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            logger.log(LOG_ERROR, "No version set in config");
        }
    }

    return _mappingConfigFileVersion;
}

bool MappingConfigManager::findMapping(std::string source, mapEntry *retMapEntry)
{
    auto ret = _mapping.find(source);
    if (ret != _mapping.end()) {
        printf("%s", (char *)(&ret->second.second));
        retMapEntry = &ret->second;
        return true;
    }
    else {
        return false;
    }
}
