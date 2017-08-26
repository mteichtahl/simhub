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
var AWS = require('aws-sdk');
var utils = require('./common/utilities');
var enums = require('./common/enum');
var config = require('./common/config');

///////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////
exports.handler = (event, context, callback) => {
  var finaliser = (err, results) => {
    callback(err, results);
  };

  try {
    init(event, context, config, (initError) => {
      if (initError) {
        finaliser(initError);
      } else {
        ////////////////////////////////////////////////
        //
        // START: This Lambda function's implementation
        //
        ////////////////////////////////////////////////

        try {
          // By default, treat the user request as coming from the
          // America/New_York time zone.
          process.env.TZ = 'America/New_York';

          var keyname = GetKeyNameFromIntent(event.currentIntent.slots.keyname);
          console.log('Keyname => ' + keyname);

          GetValueForKeyInDDB(keyname, config, (keyValueResult) => {

            if (keyValueResult.succeeded) {
              var lexResponse =
                  GenerateLexResponse(event.sessionAttributes, 'Fulfilled', {
                    contentType: 'PlainText',
                    content: 'Your current ' + keyname + ' is ' +
                        keyValueResult.data.value + ' ' +
                        keyValueResult.data.units
                  });

              console.log(lexResponse);

              callback(null, lexResponse);

            } else {
              var lexResponse =
                  GenerateLexResponse(event.sessionAttributes, 'Fulfilled', {
                    contentType: 'PlainText',
                    content:
                        'Sorry, but I couldn\'t find a reading for ' + keyname
                  });

              console.log(lexResponse);

              callback(null, lexResponse);
            }

          });
        } catch (err) {
          callback(err);
        }


        ////////////////////////////////////////////////
        //
        // END: This Lambda function's implementation
        //
        ////////////////////////////////////////////////
      }
    });
  } catch (ex) {
    var result = utils.getResultObject();
    result.errorType = enums.ErrorTypes.ERR_EXCEPTION;
    result.message = ex.message;
    finaliser(null, result);
  }
};

///////////////////////////////////////////////////////////////
//
// init()
//
///////////////////////////////////////////////////////////////
function init(event, context, config, onReadyCallback) {
  utils.init(event, context, config);
  onReadyCallback();
}


function GenerateLexResponse(sessionAttributes, fulfillmentState, message) {
  return {
    sessionAttributes,
    dialogAction: {
      type: 'Close',
      fulfillmentState,
      message,
    },
  };
}

function GetValueForKeyInDDB(keyname, config, callback) {
  var result = utils.getResultObject();

  var params = {
    TableName: utils.getDDBTableName('KeyVal', config),
    IndexName: 'title-index',
    KeyConditions: {
      'title':
          {'AttributeValueList': [{'S': keyname}], 'ComparisonOperator': 'EQ'}
    }
  }

               console.log(
                   'Calling DDB to retrieve data for keyname ' + keyname +
                   '...');

  new AWS.DynamoDB().query(params, function(err, data) {
    if (err) {
      result.message = err.message;
      result.errorType = enums.ErrorTypes.ERR_KEYNAME_LOOKUP_FAILED;

      console.log('ERROR::' + result.message);
    } else {
      if (data.Items.length == 1) {
        console.log('Found data for ' + keyname);

        var thisItem = data.Items[0];

        result.data = {
          source: (thisItem.source != null) ? thisItem.source.S : '',
          target: (thisItem.target != null) ? thisItem.target.S : '',
          value: (thisItem.value != null) ? thisItem.value.S : '',
          units: (thisItem.units != null) ? thisItem.units.S : '',
          description: (thisItem.description != null) ? thisItem.description.S :
                                                        ''
        };

        result.succeeded = true;
        result.errorType = enums.ErrorTypes.ERR_OK;
      } else {
        result.message =
            'Expecting 1 record for keyname, found ' + data.Items.length;
        result.errorType = enums.ErrorTypes.ERR_UNEXPECTED_KEYNAME_COUNT;

        console.log('ERROR::' + result.message);
      }
    }

    console.log(JSON.stringify(result));

    callback(result);
  });
}


function GetKeyNameFromIntent(keyname) {
  return keyname.replace(' ', '');
}
