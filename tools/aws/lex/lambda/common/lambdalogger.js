/*
 * Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 * http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * Author: Adam Larter, Solutions Architect, AWS
 * Created: August, 2016
 *
 * For internal Amazon purposes only! Not for distribution.
 * Contact author for more details
 *
 */

//
// Constructor
//
function LambdaLogger()
{
	//
  // Instance properties
	//
  this.consoleLogDefault      = console.log;

  return this;
}

LambdaLogger.prototype.init = function(context, config)
{
  var self = this;

  if ( !process.env['AWS_DEFAULT_REGION'] )
  {
    this.region                = config.region;
    this.functionIdentifier    = "Local Debug";
  }
  else
  {
    this.region                = process.env['AWS_DEFAULT_REGION'];
    this.functionIdentifier    = context.functionName + ":" + context.functionVersion;
  }

  this.loggingInitialised    = null;
  this.aws                   = require("aws-sdk");
  this.iotData               = new this.aws.IotData(
                               {
                                 endpoint:"data.iot." + this.region + ".amazonaws.com",
                                 region:this.region
                               });

  this.sequenceNumber        = 0;

  console.log = function(logMessage)
  {
      self.consoleLogDefault(logMessage);

      var logEvent =
      {
        topic: 'log',
        qos: 0,
        payload: JSON.stringify(
        {
          fn:self.functionIdentifier,
          seq:self.sequenceNumber++,
          log: logMessage,
          date: new Date().getTime()
        })
      };

      self.iotData.publish(
        logEvent,
        function(err, data)
        {
          if (err)
          {
            self.consoleLogDefault(err + "\n");
          }
        });
  }

}

// export the class
module.exports = new LambdaLogger();
