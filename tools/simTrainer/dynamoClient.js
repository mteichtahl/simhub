'use strict'

var color = require('cli-color');
var AWS = require('aws-sdk');

class DynamoClient {
  constructor(region, tableName) {
    this.dynamodb = new AWS.DynamoDB({region: region});
    this.tableName = tableName;
    console.log(color.green(`DynamoDB ready`));
  }

  writeItem(item, cb) {
    var params = {
      Item: item,
      ReturnConsumedCapacity: 'TOTAL',
      TableName: this.tableName
    };

    this.dynamodb.putItem(params, function(err, data) {
      if (err) {
        console.log(err);
      } else {
        cb(data);
      }
    })
  }
}

module.exports = DynamoClient