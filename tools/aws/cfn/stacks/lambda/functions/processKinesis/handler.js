var AWS = require('aws-sdk')
var _ = require('lodash')

exports.index = function (event, context, callback) {
  var ret = {
    statusCode: 200,
    headers: {'Content-Type': 'application/json'},
    body: {
      event: event,
      context: context
    }
  }
  callback(null, ret)
}
