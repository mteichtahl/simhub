#include "CLog.h"

using namespace std;

CLog logger; ///< global logging singleton

/**
  *   @brief  Default  constructor for CLog  
  *   
  *   @return nothing 
  */
CLog::CLog() {
    // set the default zlog config file name
    this->configFilename = (const char*)DEFAULT_ZLOG_CONFIG;

    // set the maximum variadic argument length
    this->maxVA_length = MAX_VA_LENGTH;

    // zlog_init() reads configuration from the file confpath.
    this->zlog = ::zlog_init(this->configFilename);

    // cannot load the zlog configuration so log an error
    if (this->zlog) {
        // display the error then return
        this->log(LOG_ERROR, "Cant load zlog config - all output will be to stdout");
    } else {
        // setup the correct categories
        this->infoCategory  = ::zlog_get_category("simhub");
        this->errorCategory = ::zlog_get_category("simhub");
        this->debugCategory = ::zlog_get_category("simhub");
        this->canZlog       = true;
        this->log(LOG_INFO, "Logging engine started.");
    }
}
/**
  *   @brief  Default  destructor for CLog  
  *   
  *   @return nothing 
  */
CLog::~CLog() {
    // display log information
    this->log(LOG_INFO, "Logging engine stopped.");

    // stop logging to zlog and return to stdout
    this->canZlog = false;

    // releases all zlog API memory and closes opened files
    zlog_fini();
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
void CLog::log(const int category, const char* pMsg, ...) {
    va_list args;               ///< variable arguement list (derived from  ...)
    char buffer[MAX_VA_LENGTH]; ///< buffer for formated output

    va_start(args, pMsg); ///< initializes args to retrieve the additional arguments after pMsg

    // zlog has failed to initialise so use stdout only
    if (!this->canZlog) {
        char* pTempMsg = (char*)malloc(strlen(pMsg)); ///< temporary message

        // copy pMsg into pTempMsg (a later strcat will modify pMsg)
        strcpy(pTempMsg, pMsg);

        //  Writes \n terminated pTempMsg format to the standard output (stdout), replacing any format specifier
        vprintf(strcat(pTempMsg, "\n"), args);

        // free pTempMsg
        free(pTempMsg);
    } else {
        // variadic printf into buffer
        vsnprintf(buffer, this->maxVA_length, pMsg, args);

        // determine which category to log into
        switch (category) {
            case LOG_INFO:
                ::zlog_info(this->infoCategory, "%s", buffer);
                break;
            case LOG_ERROR:
                ::zlog_error(this->errorCategory, "%s", buffer);
                break;
            case LOG_DEBUG:
                ::zlog_debug(this->debugCategory, "%s", buffer);
                break;
        }
    }

    // facilitate a normal return by a function that has used args (va_list)
    va_end(args);
}