'use strict'

var color = require('cli-color');
var AWS = require('aws-sdk');

class KinesisClient {
  constructor(region, streamName) {
    this.kinesis = new AWS.Firehose({region: region});
    this.kinesisPartition = 0;
    this.partitionCount = 3;
    this.streamName = streamName;
    this.kinesisEndpoint = this.kinesis.config.endpoint;

    console.log(color.green(
        `Kinesis ready (${this.kinesisEndpoint}/${this.streamName})`));
  }

  getPartition() {
    if (kinesisPartition < partitionCount) {
      return kinesisPartition.toString();
    }
    kinesisPartition++;
  }

  write(data, cb) {
    var params = {Record: {Data: data}, DeliveryStreamName: this.streamName};

    this.kinesis.putRecord(params, function(err, data) {
      if (err) {
        console.log(color.red(err.message));
      } else {
        cb(data);
      }
    })
  }
}

module.exports = KinesisClient