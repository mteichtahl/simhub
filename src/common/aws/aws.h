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
    void initKinesis(std::string streamName, std::string partition, std::string region);
    std::shared_ptr<Polly> polly(void);
    std::shared_ptr<Kinesis> kinesis(void);

protected:
    Aws::SDKOptions _options;
    std::string _SDKVersion;

    std::shared_ptr<Polly> _polly;
    std::shared_ptr<Kinesis> _kinesis;
};

#endif // __AWS_H