#ifndef __AWS_POLLY_H
#define __AWS_POLLY_H

#include "../../libs/queue/concurrent_queue.h"
#include <atomic>
#include <aws/core/Aws.h>
#include <aws/core/Version.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
#include <aws/polly/PollyClient.h>
#include <aws/text-to-speech/TextToSpeechManager.h>
#include <condition_variable>
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "common/support/threadmanager.h"

#define MAX_VA_LENGTH 4096

/**
 *  @brief Class allowing for logging to various targets based on zlog.
 */
static const char *POLLY_MAIN_ALLOCATION_TAG = "PollySample::Main";

class Polly
{
protected:
    Aws::String _defaultPollyVoice = "Amy";
    Aws::String _defaultAudioDevice = "default";

    CancelableThreadManager _threadManager;
    std::shared_ptr<Aws::Polly::PollyClient> _pollyClient;
    std::shared_ptr<Aws::TextToSpeech::TextToSpeechManager> _manager;
    ConcurrentQueue<Aws::String> _pollyQueue;
    bool _pollyCanTalk;
    int _maxVA_length; ///< maximum length (in char) of the log method variadic parameters
    void _handler(const char *, const Aws::Polly::Model::SynthesizeSpeechOutcome &, bool);

public:
    // Default constructor
    Polly(void);
    // Destructor
    ~Polly(void);
    //
    void say(const char *pMsg, ...);
    virtual void shutdown(void);
};

#endif // __AWS_POLLY_H
