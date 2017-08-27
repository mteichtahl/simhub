//
// Utilities
//
var AWS                    = require('aws-sdk');
var enums                  = require('./enum.js');

function Utils()
{
  this.lambdalogger = null;
}

Utils.prototype.constructor = Utils;

Utils.prototype.getResultObject = function()
{
  var result =
  {
    succeeded           : false,
    message             : "",
    errorType           : enums.ErrorTypes.ERR_UNKNOWN
  };

  return result;
}

///////////////////////////////////////////////////////////////
//
// init()
//
// Initialises the environment for the application in a lambda
// function call. Should be called as the first thing in all
// lambda functions as it wires up everything
//
///////////////////////////////////////////////////////////////
Utils.prototype.init = function(event, context, config)
{
  if ( !AWS.config.region )
  {
    console.log("Setting region to " + config.AWSRegion)
    AWS.config.update({region:config.AWSRegion})
  }

  //
  // Wire up the Lambda logger for debug
  //
  if ( process.env.lambdaLoggerEnabled == "true" || config.debug.lambdaLoggerEnabled )
  {
    this.lambdalogger = require("./lambdalogger");
    this.lambdalogger.init(context, config);
  }

  if ( config.debug.logEvent && event )
  {
    console.log("START: Incoming Event -->");
    console.log(JSON.stringify(event));
    console.log("END: Incoming Event <--");
  }

  //
  // Use DynamoDB local if configured to and not running in Lambda
  //
  if ( config.debug.useLocalDynamoDB && process.env['LAMBDA_TASK_ROOT'] == null )
  {
      console.log("Targetting local DynamoDB for debug -> " + config.debug.dynamoDBLocalEndpoint);
      AWS.config.dynamodb =
      {
          endpoint: config.debug.dynamoDBLocalEndpoint,
          region: config.region
      };
  }


  //
  // Override known ENVVARS
  //
  if ( process.env.memcachedConfigEndpoint )
    config.memcached.config.configEndpoint = process.env.memcachedConfigEndpoint;

}

Utils.prototype.DDBUpdateItemAsync = function(updateRequest, asyncCallback)
{
  //
  // Update DynamoDB
  //
  new AWS.DynamoDB().updateItem(
    updateRequest,
    function (ddbResponse)
    {
        if ( ddbResponse != null )
        {
            console.log("ERROR: utilities.DDBUpdateItemAsync() -> DynamoDB callback - " + ddbResponse);

            var result = {
                    succeeded           : false,
                    message             : ddbResponse.message,
                    errorType           : enums.ErrorTypes.ERR_UPDATING_DYNAMODB
            }

            asyncCallback(result);
        }
        else
        {
            var result = {
                    succeeded           : true,
                    message             : "OK",
                    errorType           : enums.ErrorTypes.ERR_OK
            }

            asyncCallback(null, result);
        }
    });
}

///////////////////////////////////////////////////////////////
//
// getDDBTableName()
//
// Returns the name of the DDB table for this build of the demo
//
///////////////////////////////////////////////////////////////
Utils.prototype.getDDBTableName = function(tableName, config)
{
  //
  // Locate the dynamoDB prefix - override from ENV vars if present
  //
  var dynamoDBPrefix = this.getCleanConfigParam(config, config.DynamoDBTablePrefix);

  if ( process.env.dynamoDBPrefix )
  {
    dynamoDBPrefix = process.env.dynamoDBPrefix;
  }

  return  dynamoDBPrefix +
          config.DynamoDBTablePrefixSeparator +
          config.DynamoDBTableNames[tableName];
}

Utils.prototype.getCleanConfigParam = function(config, paramValue)
{
  var configCFNStackPrefix = config.CFNStackPrefix;

  if ( process.env.cfnStackName )
  {
    configCFNStackPrefix = process.env.cfnStackName;
  }

  var configAWSAccountId = config.AWSAccountId;
  if ( process.env.awsAccountId )
  {
    configAWSAccountId = process.env.awsAccountId;
  }

  var configAWSRegion = config.AWSRegion;
  if ( process.env.awsRegion )
  {
    configAWSRegion = process.env.awsRegion;
  }

  paramValue = paramValue.replace(/<CFN_STACKNAME>/ig,    configCFNStackPrefix);
  paramValue = paramValue.replace(/<AWS_ACCOUNTID>/ig,    configAWSAccountId);
  paramValue = paramValue.replace(/<AWS_REGION>/ig,       configAWSRegion);
  paramValue = paramValue.replace(/<AWS_REGION_SHORT>/ig, configAWSRegion.replace(/[^\w\s]/gi, ''));

  return paramValue;
}

module.exports = new Utils();
