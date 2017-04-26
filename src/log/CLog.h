#ifndef __CLOG_H
#define __CLOG_H

#include <cstdarg>
#include <iostream>
#include <string>
#include <zlog.h>

using namespace std;

#define DEFAULT_ZLOG_CONFIG "config/zlog.conf"
#define LOG_INFO 1
#define MAX_VA_LENGTH 4096

class CLog {
public:
    CLog();
    ~CLog();
    void log(const int category, const char* msg, ...);

protected:
    bool canZlog; // true when using zlog, cout otherwise
    const char* configFilename; // location of the zlong configuration file
    zlog_category_t* infoCategory;
    int zlog;
    int vaLength;
};

extern CLog logger;

#endif