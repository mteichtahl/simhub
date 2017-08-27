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

    _recordCounter = 0;

    _thread = std::make_shared<std::thread>([=] {
        _threadRunning = true;
        logger.log(LOG_INFO, " - Starting AWS Kinesis Service...");
        while (!_threadCancelled) {
            try {
                Aws::Utils::ByteBuffer data = _queue.pop(); ///< grab an item off the queue
                Aws::Kinesis::Model::PutRecordRequest *request = new Aws::Kinesis::Model::PutRecordRequest();
                request->SetStreamName(Aws::String(_streamName.c_str()));
                request->WithData(data).WithPartitionKey(Aws::String(_partition.c_str()));
                _kinesisClient->PutRecord(*request);
                _recordCounter++;
            }
            catch (ConcurrentQueueInterrupted &except) {
            }
        }
        _threadRunning = false;
        logger.log(LOG_INFO, " - Terminated AWS Kinesis Service");
    });
}

Kinesis::~Kinesis()
{
    logger.log(LOG_INFO, " - AWS Kinesis stopped");
}

void Kinesis::putRecord(Aws::Utils::ByteBuffer data)
{
    _queue.push(data);
}
