#ifndef __AWS_POLLY_H
#define __AWS_POLLY_H

#include "../../libs/queue/concurrent_queue.h"
#include <aws/core/Aws.h>
#include <aws/polly/PollyClient.h>
#include <aws/core/Version.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
#include <aws/text-to-speech/TextToSpeechManager.h>
#include <condition_variable>
#include <cstdarg>
#include <atomic>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "appsupport.h"
#define MAX_VA_LENGTH 4096

/**
 *  @brief Class allowing for logging to various targets based on zlog.
 */
static const char *POLLY_MAIN_ALLOCATION_TAG = "PollySample::Main";

class Polly : public CancellableThread
{
public:
    // Default constructor
    Polly(void);
    // Destructor
    ~Polly(void);
    //
    void say(const char *pMsg, ...);
    virtual void shutdown(void)
    {
        _pollyQueue.unblock();
        CancellableThread::shutdown();
    };

protected:
    Aws::String _defaultPollyVoice = "Nicole";
    Aws::String _defaultAudioDevice = "default";

    std::shared_ptr<Aws::Polly::PollyClient> _pollyClient;
    std::shared_ptr<Aws::TextToSpeech::TextToSpeechManager> _manager;
    ConcurrentQueue<Aws::String> _pollyQueue;
    bool _pollyCanTalk;
    int _maxVA_length; ///< maximum length (in char) of the log method variadic parameters
    void _handler(const char *, const Aws::Polly::Model::SynthesizeSpeechOutcome &, bool);
};

#endif // __AWS_POLLY_H
