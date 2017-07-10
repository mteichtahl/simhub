#include <unistd.h>

#include "../log/clog.h"
#include "aws.h"

AWS awsHelper;

AWS::AWS()
{
    _options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    _options.loggingOptions.defaultLogPrefix = "../logs/aws/";
    _SDKVersion = Aws::Version::GetVersionString();
}

AWS::~AWS()
{
    Aws::ShutdownAPI(_options);
}

Polly *AWS::polly()
{
    return _polly;
}

void AWS::initPolly()
{
    _polly = new Polly;
}

void AWS::init()
{
    Aws::InitAPI(_options);
    logger.log(LOG_INFO, "AWS SDK v%s started", _SDKVersion.c_str());
}
