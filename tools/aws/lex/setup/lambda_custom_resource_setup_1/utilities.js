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
  if ( config.debug.logEvent)
  {
    console.log("START: Incoming Event -->");
    console.log(JSON.stringify(event));
    console.log("END: Incoming Event <--");
  }

  if ( !AWS.config.region )
  {
    AWS.config.region = config.region;
  }
}

module.exports = new Utils();
