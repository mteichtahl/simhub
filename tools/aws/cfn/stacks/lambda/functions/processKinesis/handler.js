var AWS = require('aws-sdk');
var _ = require('lodash');
var base64 = require('base-64');
var AWS = require('aws-sdk');
var s3 = new AWS.S3();

var cloudwatch = new AWS.CloudWatch();
var dynamodb = new AWS.DynamoDB();

/**
 * cleanJSONString
 *
 * @param {any} string string that requires cleaning
 * @returns string cleaned string
 */
function cleanJSONString(string) {
  // preserve newlines, etc - use valid JSON
  string = string.replace(/\\n/g, '\\n')
               .replace(/\\'/g, '\\\'')
               .replace(/\\"/g, '\\"')
               .replace(/\\&/g, '\\&')
               .replace(/\\r/g, '\\r')
               .replace(/\\t/g, '\\t')
               .replace(/\\b/g, '\\b')
               .replace(/\\f/g, '\\f');
  // remove non-printable and other non-valid JSON chars
  return string.replace(/[\u0000-\u0019]+/g, '');
}

function writeToDynamo(name, value, units, description) {
  var params = {
    Item: {
      'source': {S: name},
      'value': {S: value},
      'units': {S: units},
      'description': {S: description}
    },
    ReturnConsumedCapacity: 'TOTAL',
    TableName: 'simhub'
  };

  dynamodb.putItem(params, function(err, data) {
    if (err)
      console.log(err, err.stack);  // an error occurred
    else
      console.log(data);  // successful response
  });
}

function putCloudwatchMetric(metricName, dimName, dimValue, ts, value) {
  var params = {
    MetricData: [
      /* required */
      {
        MetricName: metricName,
        Dimensions: [
          {Name: dimName, Value: dimValue},
        ],
        StorageResolution: 1,
        Timestamp: new Date(ts).toISOString(),
        Unit: 'None',
        Value: parseFloat(value)
      },

    ],
    Namespace: 'simhub' /* required */
  };

  cloudwatch.putMetricData(params, function(err, data) {
    if (err)
      console.log(err, err.stack);  // an error occurred
    else
      console.log(data);  // successful response
  });
}

/**
 * Main lambda handler and entry point
 */
exports.index = function(event, context, callback) {
  // find the number of records being given to us by kinesis
  var recordCount = event.Records.length;

  // iterate through the records
  for (i = 0; i < recordCount; i++) {
    // get the kinesis payload
    var kinesis = event.Records[i].kinesis;

    // convert from base64, clean up and "funny" characters and parse into
    // JSON
    console.log(kinesis.data);
    console.log(base64.decode(kinesis.data));
    data = JSON.parse(cleanJSONString(base64.decode(kinesis.data)));

    putCloudwatchMetric(data.s, data.s, 'On/Off', parseInt(data.ts), data.val);


    writeToDynamo(data.s, data.val, data.u, data.d);
  }


  callback(null, 'Complete');
}
