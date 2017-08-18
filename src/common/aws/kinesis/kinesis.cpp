#include <unistd.h>

#include "../../log/clog.h"
#include "kinesis.h"
#if defined(_AWS_SDK)
#include "../aws.h"
#endif

Kinesis::Kinesis(Aws::String streamName, Aws::String partition, Aws::String region)
    : _partition(partition)
    , _streamName(streamName)
    , _region(region)
{

    Aws::Client::ClientConfiguration config;
    _kinesisClient = Aws::MakeShared<KinesisClient>(ALLOCATION_TAG, config);

    logger.log(LOG_INFO, " - Starting AWS Kinesis Service...");

    _thread = new std::make_shared<std::thread>([=] {
        while (true) {
            Aws::Utils::ByteBuffer data = _queue.pop(); ///< grab an item off the queue
            Aws::Kinesis::Model::PutRecordRequest *request = new Aws::Kinesis::Model::PutRecordRequest();
            request->SetStreamName(_streamName);
            request->WithData(data).WithPartitionKey(_partition);
            _kinesisClient->PutRecord(*request);
        }
    });
}

std::shared_ptr<std::thread> Kinesis::thread()
{
    return _thread;
}

bool Kinesis::isJoinable()
{
    return _thread->joinable();
}

Kinesis::~Kinesis()
{
    logger.log(LOG_INFO, " - AWS Kinesis stopped");
}

bool Kinesis::putRecord(Aws::Utils::ByteBuffer data)
{
    // TODO: Assert here ?
    _queue.push(data);
    return 0;
}
