#ifndef __AWS_H
#define __AWS_H

#include <aws/core/Aws.h>
#include <aws/core/Version.h>
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
    bool init();
    void say(const char *text, ...);

protected:
    Aws::SDKOptions _options;
    std::string _SDKVersion;
    Aws::String _defaultPollyVoice = "Joanna";
    Aws::String _defaultAudioDevice = "default";
    Aws::TextToSpeech::SendTextCompletedHandler _handlerFunction;
    Aws::TextToSpeech::TextToSpeechManager *_textToSpeechManager;
    int _maxVA_length;
    static void handler(const char *, const Aws::Polly::Model::SynthesizeSpeechOutcome &, bool);

private:
    void initPolly(void);
};

extern AWS awsHelper; ///< allow externals to access logger

#endif // __AWS_H