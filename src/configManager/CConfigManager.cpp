#include "CConfigManager.h"

CConfigManager::CConfigManager(string filename) {
    if (this->fileExists(filename)) {
        this->configFilename = filename;
    } else {
        logger.log(LOG_ERROR, "Config file %s does not exist", filename.c_str());
    }
}

bool CConfigManager::fileExists(const std::string& Filename) {
    return access(Filename.c_str(), 0) == 0;
}

string CConfigManager::getConfigFilename() {
    return this->configFilename;
}
