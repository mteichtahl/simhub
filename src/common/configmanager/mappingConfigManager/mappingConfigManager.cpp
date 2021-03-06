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
    logger.log(LOG_INFO, "Mapping | Closing mapping configuration");
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

std::string MappingConfigManager::configFilename(void)
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
        logger.log(LOG_INFO, "Mapping | %d mapping(s)", _mappingConfig->getLength());

        // no need to continue if there are no mappings to be processed
        if (_mappingConfig->getLength() == 0) {
            return RETURN_OK;
        }

        for (int i = 0; i <= _mappingConfig->getLength() - 1; i++) {
            std::string source;
            std::string target;
            unsigned int sustain = 0;

            try {
                source = (const char *)(*_mappingConfig)[i].lookup("source");
                target = (const char *)(*_mappingConfig)[i].lookup("target");
                (*_mappingConfig)[i].lookupValue("sustain", sustain);
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                logger.log(LOG_ERROR, "Mapping | WARNING | Config file parse error at %s. Skipping....", nfex.getPath());
                continue;
            }
            catch (const libconfig::SettingTypeException &nfex) {
                logger.log(LOG_ERROR, "Mapping | WARNING | Setting type error for %s. Skipping....", nfex.getPath());
                continue;
            }

            if (mapContains(_mapping, source)) {
                logger.log(LOG_INFO, "Mapping | WARNING | Skipping duplicate source %s ", source.c_str());
                continue;
            }
            else {
                _mapping[source] = std::make_pair(source, target);
                logger.log(LOG_INFO, "Mapping | %s to %s", source.c_str(), target.c_str());
            }

            if (sustain > 0 && !mapContains(_sustainMap, source)) {
                _sustainMap[source] = sustain;
            }
        }
        logger.log(LOG_INFO, "Mapping | %i Mappings", _mapping.size());
    }
    catch (std::exception &e) {
        logger.log(LOG_ERROR, "Mapping | %s", e.what());
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
            logger.log(LOG_ERROR, "<WARNING> <ERROR> No version set in config");
        }
    }

    return _mappingConfigFileVersion;
}

/**
 *   @brief find a source and target pair based on a source
 *
 *   @param  std::string A string representing the name of the source element
 *   @param  MapEntry MapEntry to return into
 *
 *   @return bool true if file exists, otherwise false
 */
bool MappingConfigManager::find(std::string key, MapEntry **retMapEntry)
{
    ElementMap::iterator ret = _mapping.find(key);
    if (ret != _mapping.end()) {
        *retMapEntry = &(ret->second);
        return true;
    }
    else {
        // provide a default mapping
        return true;
    }
}
