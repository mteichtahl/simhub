#ifndef __AWS_H
#define __AWS_H

#include "../../libs/queue/concurrent_queue.h"
#include <aws/core/Aws.h>
#include <aws/core/Version.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
#include <aws/text-to-speech/TextToSpeechManager.h>
#include <condition_variable>
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_VA_LENGTH 4096

static const char *POLLY_ALLOCATION_TAG = "PollySample::Main";

/**
 *  @brief Class allowing for logging to various targets based on zlog.
 */
class AWS
{

public:
    // Default constructor
    AWS(void);
    // Destructor
    ~AWS(void);
    void init();
    void pollySay(std::string);
    std::thread initPolly(bool);

protected:
    Aws::SDKOptions _options;
    std::string _SDKVersion;
    Aws::String _defaultPollyVoice = "Nicole";
    Aws::String _defaultAudioDevice = "default";
    void _handler(const char *, const Aws::Polly::Model::SynthesizeSpeechOutcome &, bool);
    std::shared_ptr<Aws::Polly::PollyClient::PollyClient> _pollyClient;
    std::shared_ptr<Aws::TextToSpeech::TextToSpeechManager> _manager;
    bool _pollyCanTalk;

    ConcurrentQueue<Aws::String> _pollyQueue;
};

extern AWS awsHelper; ///< allow externals to access logger

#endif // __AWS_H