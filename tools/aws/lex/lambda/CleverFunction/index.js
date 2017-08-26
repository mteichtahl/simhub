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
 * Author: Adam Larter, Developer Solutions Architect, AWS
 * Created: January 2017
 *
 */

///////////////////////////////////////////////////////////////
//
// Configuration
//
///////////////////////////////////////////////////////////////
var AWS                    = require('aws-sdk');
var config                 = require('./common/config');
var utils                  = require('./common/utilities');

///////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////

exports.handler = (event, context, callback) =>
{
  var finaliser = (err, results) =>
  {
    callback(err, results);
  };

  try
  {
   init(event, context, config, (initError)=>
   {
     if ( initError )
     {
       finaliser(initError);
     }
     else
     {
       ////////////////////////////////////////////////
       //
       // START: This Lambda function's implementation
       //
       ////////////////////////////////////////////////

       var result             = utils.getResultObject();
       result.message         = "Success";
       result.succeeded       = true;

       finaliser(null, result);

       ////////////////////////////////////////////////
       //
       // END: This Lambda function's implementation
       //
       ////////////////////////////////////////////////

     }
    });
  }
  catch (ex)
  {
   var result             = utils.getResultObject();
   result.errorType       = enums.ErrorTypes.ERR_EXCEPTION;
   result.message         = ex.message;
   finaliser(null, result);
  }
};

///////////////////////////////////////////////////////////////
//
// init()
//
///////////////////////////////////////////////////////////////
function init(event, context, config, onReadyCallback)
{
  utils.init(event, context, config);
  onReadyCallback();
}
