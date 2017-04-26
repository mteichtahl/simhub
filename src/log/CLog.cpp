#include "CLog.h"

using namespace std;

CLog logger;

CLog::CLog()
{
    // logging is not yet enabled (cout will be used until it is)

    // set the default zlog config file name
    this->configFilename = (const char*)DEFAULT_ZLOG_CONFIG;
    // load the
    this->zlog = ::zlog_init(this->configFilename);

    if (this->zlog) {
        this->log(LOG_INFO, "cant load zlog config");
    }
    else {
        this->infoCategory = ::zlog_get_category("simhub");
        this->vaLength = MAX_VA_LENGTH;
        this->canZlog = true;
    }
    log(LOG_INFO, "ok %s %s", "test");
}

CLog::~CLog()
{
    this->log(LOG_INFO, "shutting down logging");
    this->canZlog = false;
    zlog_fini();
}

/**
*   global logging method
*
*   log to a specific logging target as defined in config/zlog.conf
*
*    @string msg         message to the looged to category
*    @int    categoryId  category to log into
**/
void CLog::log(const int category, const char* pMsg, ...)
{

    va_list args;
    char buffer[4096];

    va_start(args, pMsg);

    vsnprintf(buffer, this->vaLength, pMsg, args);

    if (!this->canZlog) {
        printf("%s", buffer);
    }
    else {
        if (category == LOG_INFO) {
            ::zlog_info(this->infoCategory, "%s", buffer);
        }
    }

    va_end(args);
}