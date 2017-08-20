var AWS = require('aws-sdk');
var _ = require('lodash');
var base64 = require('base-64');

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

    // convert from base64, clean up and "funny" characters and parse into JSON
    data = JSON.parse(cleanJSONString(base64.decode(kinesis.data)));

    console.log(data);
  }


  callback(null, 'Hello from Lambda');
}
