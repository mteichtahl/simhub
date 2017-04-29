#include "configmanager.h"

CConfigManager::CConfigManager(string filename)
{
    if (fileExists(filename)) {
        _configFilename = filename;
    }
    else {
        logger.log(LOG_ERROR, "Config file %s does not exist", filename.c_str());
    }
}

bool CConfigManager::fileExists(std::string filename)
{
    return (filename.size() > 0 && access(filename.c_str(), 0) == 0);
}

std::string CConfigManager::getConfigFilename(void)
{
    return _configFilename;
}
