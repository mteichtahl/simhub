#ifndef __CLOG_H
#define __CLOG_H

#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <zlog.h>

using namespace std;

#define DEFAULT_ZLOG_CONFIG "config/zlog.conf"

enum logCategory {
    LOG_INFO  = 1,
    LOG_ERROR = 2,
    LOG_DEBUG = 3
};

#define MAX_VA_LENGTH 4096

/**
  *  @brief Class allowing for logging to various targets based on zlog.  
  */
class CLog {
public:
    // Default constructor
    CLog();
    // Destructor
    ~CLog();
    // log @msg to specific @category - uses variadic parameters
    void log(const int category, const char* msg, ...);

protected:
    bool canZlog;                   ///< true when using zlog, cout otherwise
    const char* configFilename;     ///< location of the zlong configuration file
    zlog_category_t* infoCategory;  ///< a zlog category for informational logging
    zlog_category_t* errorCategory; ///< a zlog category for error logging
    zlog_category_t* debugCategory; ///< a zlog category for error logging
    int zlog;                       ///< the zlog handler
    int maxVA_length;               ///< maximum length (in char) of the log method variadic parameters
};

extern CLog logger; ///< allow externals to access logger

#endif // __CLOG_H