#include <unistd.h>

#include "../log/clog.h"
#include "aws.h"

AWS awsHelper;

AWS::AWS()
    : _textToSpeechManager(NULL)
{
    _options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    _options.loggingOptions.defaultLogPrefix = "../logs/aws/";
    _SDKVersion = Aws::Version::GetVersionString();
    _maxVA_length = MAX_VA_LENGTH;
}

AWS::~AWS()
{

    if (_textToSpeechManager != NULL)
        delete _textToSpeechManager;

    Aws::ShutdownAPI(_options);
}

void AWS::initPolly(void)
{
    logger.log(LOG_INFO, " - Starting Polly text to speech");
    auto client = Aws::MakeShared<Aws::Polly::PollyClient>(POLLY_ALLOCATION_TAG);
    _textToSpeechManager = new Aws::TextToSpeech::TextToSpeechManager(client);
    auto devices = _textToSpeechManager->EnumerateDevices();
    for (auto &device : devices) {
        logger.log(LOG_INFO, "  - %s %s [%s]", device.first.deviceName.c_str(), device.second->GetName(), device.first.deviceId.c_str());
    }
    Aws::String deviceId = _defaultAudioDevice;
    auto foundDevice = std::find_if(devices.begin(), devices.end(), [&deviceId](const Aws::TextToSpeech::OutputDevicePair &device) { return device.first.deviceId == deviceId; });
    _textToSpeechManager->SetActiveVoice(_defaultPollyVoice);
}

void AWS::say(const char *text, ...)
{
    va_list args; ///< variable arguement list (derived from  ...)
    char buffer[MAX_VA_LENGTH]; ///< buffer for formated output

    va_start(args, text); ///< initializes args to retrieve the additional arguments after pMsg
    vsnprintf(buffer, _maxVA_length, text, args);
    _textToSpeechManager->SendTextToOutputDevice(buffer, AWS::handler);
}

bool AWS::init()
{
    Aws::InitAPI(_options);
    logger.log(LOG_INFO, "AWS SDK v%s started", _SDKVersion.c_str());

    initPolly();

    awsHelper.say("AWS Polly is ready %d", 1);
    awsHelper.say("Loading configuration file");

    return true;
}

void AWS::handler(const char *device, const Aws::Polly::Model::SynthesizeSpeechOutcome &res, bool ret)
{
    // std::cout << ret << std::endl;
}
