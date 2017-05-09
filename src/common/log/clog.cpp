#include "clog.h"

CLog logger; ///< global logging singleton

/**
 *   @brief  Default  constructor for CLog
 *
 *   @return nothing
 */
CLog::CLog()
{
    // default to not being able to log to zLog but to stdout
    canZlog = false;
}
/**
 *   @brief  Default  destructor for CLog
 *
 *   @return nothing
 */
CLog::~CLog()
{

    if (canZlog) {
        // stop logging to zlog and return to stdout
        canZlog = false;
        // releases all zlog API memory and closes opened files
        ::zlog_fini();
    }
}

bool CLog::init(std::string configFilename)
{

    if (configFilename.empty()) {
        log(LOG_ERROR, "No logging configuration file specified");
        canZlog = false;
        return false;
    }

    // set the default zlog config file name - defaults to config/zlog.conf
    _configFilename = configFilename;

    // set the maximum variadic argument length
    maxVA_length = MAX_VA_LENGTH;

    // zlog_init() reads configuration from the file confpath.
    zlog = zlog_init(_configFilename.c_str());

    // cannot load the zlog configuration so log an error
    if (zlog < 0) {
        // display the error then return
        log(LOG_ERROR, "Cant load zlog config %s - All output will be to stdout", _configFilename.c_str());
        canZlog = false;
        return false;
    }
    else {
        // setup the correct categories
        infoCategory = ::zlog_get_category("simhub");
        errorCategory = ::zlog_get_category("simhub");
        debugCategory = ::zlog_get_category("simhub");

        // now we can start logging to the the zlog categories (rather the stdout)
        canZlog = true;
        log(LOG_INFO, "Logging engine v%s started.", ::zlog_version());
        return true;
    }
}

/**
 *   @brief log a message to a zlog category
 *
 *   @param  category is an int, category to log to (see: logCategory enum)
 *   @param  pMsg is a char pointer to the message/format element
 *   @param  ... a variadic (variable length) set of parameters
 *
 *   @return nothing
 */
void CLog::log(const int category, const char *pMsg, ...)
{
    va_list args; ///< variable arguement list (derived from  ...)
    char buffer[MAX_VA_LENGTH]; ///< buffer for formated output

    va_start(args, pMsg); ///< initializes args to retrieve the additional arguments after pMsg

    // zlog has failed to initialise so use stdout only
    if (!canZlog) {
        char *pTempMsg = (char *)malloc(strlen(pMsg) + 2); ///< temporary message, making room for \0 and \n

        // copy pMsg into pTempMsg (a later strcat will modify pMsg)
        strcpy(pTempMsg, pMsg);

        //  Writes \n terminated pTempMsg format to the standard output (stdout), replacing any format specifier
        vprintf(strcat(pTempMsg, "\n"), args);

        // free pTempMsg
        free(pTempMsg);
    }
    else {
        // variadic printf into buffer
        vsnprintf(buffer, maxVA_length, pMsg, args);

        // determine which category to log into
        switch (category) {
        case LOG_INFO:
            ::zlog_info(infoCategory, "%s", buffer);
            break;
        case LOG_ERROR:
            ::zlog_error(errorCategory, "%s", buffer);
            break;
        case LOG_DEBUG:
            ::zlog_debug(debugCategory, "%s", buffer);
            break;
        }
    }

    // facilitate a normal return by a function that has used args (va_list)
    va_end(args);
}
