#include <unistd.h>

#include "../../log/clog.h"
#include "kinesis.h"
#if defined(_AWS_SDK)
#include "../aws.h"
#endif

Kinesis::Kinesis(std::string streamName, std::string partition, std::string region)
    : _partition(partition)
    , _streamName(streamName)
    , _region(region)
{

    Aws::Client::ClientConfiguration config;
    config.region = Aws::String(_region.c_str());
    _kinesisClient = Aws::MakeShared<KinesisClient>(ALLOCATION_TAG, config);

    logger.log(LOG_INFO, " - Starting AWS Kinesis Service...");

    _thread = std::make_shared<std::thread>([=] {
        while (true) {
            Aws::Utils::ByteBuffer data = _queue.pop(); ///< grab an item off the queue
            Aws::Kinesis::Model::PutRecordRequest *request = new Aws::Kinesis::Model::PutRecordRequest();
            request->SetStreamName(Aws::String(_streamName.c_str()));
            request->WithData(data).WithPartitionKey(Aws::String(_partition.c_str()));
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

void Kinesis::putRecord(Aws::Utils::ByteBuffer data)
{
    _queue.push(data);
}
