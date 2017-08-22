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

std::shared_ptr<Polly> AWS::polly(void)
{
    return _polly;
}

std::shared_ptr<Kinesis> AWS::kinesis(void)
{
    return _kinesis;
}

void AWS::initPolly()
{
    _polly = std::make_shared<Polly>();
}

void AWS::initKinesis(std::string streamName, std::string partition, std::string region)
{
    // TODO: Make this part of a config file
    _kinesis = std::make_shared<Kinesis>(streamName, partition, region);
}

void AWS::init()
{
    Aws::InitAPI(_options);
    logger.log(LOG_INFO, "AWS SDK v%s started", _SDKVersion.c_str());
}
