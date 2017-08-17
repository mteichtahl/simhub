#ifndef __AWS_KINESIS_H
#define __AWS_KINESIS_H

#include "../../libs/queue/concurrent_queue.h"
#include <aws/core/Aws.h>
#include <aws/core/Version.h>
#include <aws/core/utils/Outcome.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
#include <aws/kinesis/KinesisClient.h>
#include <aws/kinesis/model/PutRecordRequest.h>
#include <condition_variable>
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_VA_LENGTH 4096

typedef Aws::Kinesis::KinesisClient KinesisClient;

static const char *ALLOCATION_TAG = "Kinesis::Main";
class Kinesis
{

public:
    // Default constructor
    Kinesis(Aws::String streamName, Aws::String partition, Aws::String region);
    // Destructor
    ~Kinesis(void);
    //
    std::thread *thread(void);
    bool isJoinable();
    bool putRecord(Aws::Utils::ByteBuffer data);

protected:
    std::shared_ptr<KinesisClient> _kinesisClient; ///< main kinesis client

    ConcurrentQueue<Aws::Utils::ByteBuffer> _queue;
    std::thread *_thread;
    int _maxVA_length; ///< maximum length (in char) of the log method variadic parameters
    Aws::String _partition;
    Aws::String _streamName;
    Aws::String _region;
};

#endif // Kinesis
