var AWS = require('aws-sdk');
var _ = require('lodash');
var base64 = require('base-64');

exports.index = function(event, context, callback) {
  var recordCount = event.Records.length;
  console.log(recordCount);

  for (i = 0; i < recordCount; i++) {
    var kinesis = event.Records[i].kinesis;
    data = base64.decode(kinesis.data);
    console.log(data);
  }


  callback(null, 'Hello from Lambda');
}
