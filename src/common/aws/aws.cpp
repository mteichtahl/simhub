#include "aws.h"
#include "../log/clog.h"

AWS awsHelper;

AWS::AWS()
{
}

AWS::~AWS()
{
}

bool AWS::init()
{
    logger.log(LOG_INFO, "No logging configuration file specified");
    return true;
}