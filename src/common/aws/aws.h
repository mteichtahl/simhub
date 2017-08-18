#ifndef __AWS_H
#define __AWS_H

#include "../../libs/queue/concurrent_queue.h"
#include "kinesis/kinesis.h"
#include "polly/polly.h"
#include <aws/core/Aws.h>
#include <aws/core/Version.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
#include <aws/text-to-speech/TextToSpeechManager.h>
#include <condition_variable>
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>

class AWS
{

public:
    // Default constructor
    AWS(void);
    // Destructor
    ~AWS(void);
    void init();
    void initPolly(void);
    void initKinesis(void);
    Polly *polly();
    Kinesis *kinesis();

protected:
    Aws::SDKOptions _options;
    std::string _SDKVersion;

    Polly *_polly;
    Kinesis *_kinesis;
};

extern AWS awsHelper; ///< allow externals to access logger

#endif // __AWS_H