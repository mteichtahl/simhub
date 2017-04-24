#include "CConfigManager.h"

CConfigManager::CConfigManager(string filename)
{
    if (this->fileExists(filename))
        this->configFileName = filename;
    else {
        cout << "No config file found";
    }
}

bool CConfigManager::fileExists(const std::string& Filename)
{
    return access(Filename.c_str(), 0) == 0;
}
