#include <unistd.h>

#include "../log/clog.h"
#include "aws.h"

AWS awsHelper;

AWS::AWS()
{
    _pollyCanTalk = false;
    _options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    _options.loggingOptions.defaultLogPrefix = "../logs/aws/";
    _SDKVersion = Aws::Version::GetVersionString();
}

AWS::~AWS()
{
    Aws::ShutdownAPI(_options);
}

std::thread AWS::initPolly(bool usePolly)
{
    if (!usePolly) {
        _pollyCanTalk = false;
        return std::thread([=] {});
    }
    _pollyClient = Aws::MakeShared<Aws::Polly::PollyClient::PollyClient>(POLLY_ALLOCATION_TAG);
    _manager = std::make_shared<Aws::TextToSpeech::TextToSpeechManager>(_pollyClient);

    _manager->SetActiveVoice(_defaultPollyVoice.c_str());
    _pollyCanTalk = true;

    return std::thread([=] {
        logger.log(LOG_INFO, " - Starting Polly text to speech");
        pollySay("Voice integration activated");

        while (true) {
            if (_pollyCanTalk) {
                auto item = _pollyQueue.pop();
                using namespace std::placeholders;
                _manager->SendTextToOutputDevice(item.c_str(), std::bind(&AWS::_handler, this, _1, _2, _3));
                _pollyCanTalk = false;
            }
        }
    });
}

void AWS::pollySay(std::string text)
{
    _pollyQueue.push(text.c_str());
}

void AWS::init()
{
    Aws::InitAPI(_options);
    logger.log(LOG_INFO, "AWS SDK v%s started", _SDKVersion.c_str());
}

void AWS::_handler(const char *device, const Aws::Polly::Model::SynthesizeSpeechOutcome &res, bool ret)
{
    _pollyCanTalk = true;
}
