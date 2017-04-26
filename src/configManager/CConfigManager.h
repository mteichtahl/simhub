#ifndef __CCONFIGMANAGER_H
#define __CCONFIGMANAGER_H

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif

#include <iostream>
#include <libconfig.h++>
#include <map>
#include <string>

#include "../log/CLog.h"

using namespace std;

/**
Base class for all pin based classes
**/
class CConfigManager {
    libconfig::Config config;
    string configFileName;

public:
    CConfigManager(string);

protected:
    bool fileExists(const string& filename);

private:
};
#endif