#include <unistd.h>

#include "../../log/clog.h"
#include "polly.h"

Polly::Polly()
{
    _pollyCanTalk = false; ///< No talking while we instantiate
    _maxVA_length = MAX_VA_LENGTH; ///< set the maximum variadic argument length
    _pollyClient = Aws::MakeShared<Aws::Polly::PollyClient>(POLLY_MAIN_ALLOCATION_TAG); ///< create the AWS SDK client
    _manager = std::make_shared<Aws::TextToSpeech::TextToSpeechManager>(_pollyClient); ///< create TTS manager
    _manager->SetActiveVoice(_defaultPollyVoice.c_str()); ///< set the active voice
    
    // this is the worker thread - it blocks on _pollQueue until there is something to read

    std::shared_ptr<std::thread> pollyThread  = std::make_shared<std::thread>([=] {
        _threadManager.setThreadRunning(true);
        logger.log(LOG_INFO, " - Starting AWS Polly Service...");
        while (!_threadManager.threadCanceled()) {
            if (_pollyCanTalk) { ///< only do this if we are allowed to talk
                try {
                    auto item = _pollyQueue.pop(); ///< grab an item off the queue
                    using namespace std::placeholders;
                    _manager->SendTextToOutputDevice(item.c_str(), std::bind(&Polly::_handler, this, _1, _2, _3)); ///< send to AWS
                    _pollyCanTalk = false; ///< be quiet until the callback
                }
                catch (ConcurrentQueueInterrupted &except) {
                }
            }
        }
        _threadManager.setThreadRunning(false);
        logger.log(LOG_INFO, " - Terminated AWS Polly Service");
    });

    _threadManager.setManagedThread(pollyThread);

    _pollyCanTalk = true; ///< we can start talking because everything is ready to go
}

void Polly::shutdown(void)
{
    _pollyQueue.unblock();
    _threadManager.shutdownThread();

    // abort async operations
    _pollyClient->DisableRequestProcessing();

    // allow internall PollyClient threads to stop
    std::this_thread::sleep_for(1000ms);

    _pollyClient.reset();
}

void Polly::say(const char *pMsg, ...)
{

    va_list args; ///< variable arguement list (derived from  ...)
    char buffer[MAX_VA_LENGTH]; ///< buffer for formated output

    va_start(args, pMsg); ///< initializes args to retrieve the additional arguments after pMsg
    vsnprintf(buffer, _maxVA_length, pMsg, args); ///< variadic printf into buffer

    _pollyQueue.push(buffer); ///< enqueue the buffer to the API

    va_end(args); ///< finish with our variable arguement list
}

Polly::~Polly()
{
    _pollyCanTalk = false;
    logger.log(LOG_INFO, " - AWS Polly stopped");
}

void Polly::_handler(const char *device, const Aws::Polly::Model::SynthesizeSpeechOutcome &res, bool ret)
{
    _pollyCanTalk = true; ///< once the callback has completed we can talk again
}
