
var async                 = require('async');
var g_event		 				    = null;
var g_context 				    = null;
var utils                 = require('./common/utilities');
var TEMPLATE_PREFIX       = "";
var STACKNAME_SAFE        = "";
var RESOURCE_PREFIX       = "KeyValQuery";
var LEXBOTHANDLER_ARN     = "";
var AWS         		      = require('aws-sdk');
var fs                    = require('fs');
var libTmp                = require('tmp');

//
// Globals
//
var g_resources    		  = {};

exports.handler = function (event, context)
{
    if ( !AWS.config.region )
      AWS.config.region = "us-east-1";

    console.log(JSON.stringify(event));

    //
    // initialise globals for this run
    //
    g_context     = context;
    g_event	      = event;
    g_resources   = {};
    g_propertyBag = {};

    TEMPLATE_PREFIX       = event.ResourceProperties.StackName.replace(/[^\w\s]/gi, '') + "_" + event.ResourceProperties.Region.replace(/[^\w\s]/gi, '') + "_" + RESOURCE_PREFIX;
    STACKNAME_SAFE        = event.ResourceProperties.StackName.replace(/[^a-zA-Z]/gi,'');
    LEXBOTHANDLER_ARN     = event.ResourceProperties.LexBotHandlerARN;
    console.log("LexBotHandlerARN = " + event.ResourceProperties.LexBotHandlerARN);

    try
    {
        if (event.RequestType == 'Delete')
        {
          unconfigureResources(event.ResourceProperties, function(err, result)
          {
            var status = err ? 'FAILED' : 'SUCCESS';
            return sendResponse(event, context, status, result, err);
          });
        }
        else
        {
            configureResources(event.ResourceProperties, function(err, result)
            {
                var status = err ? 'FAILED' : 'SUCCESS';
                return sendResponse(event, context, status, result, err);
            });
        }
    }
    catch(ex)
    {
        console.log("EXCEPTION::Outer Catch --> " + ex.message);
        return sendResponse(event, context, 'FAILED', ex.message, ex);
    }
}

function SetResultAsError(err)
{
	g_resources.Succeeded 		= false;
	g_resources.ErrorMessage 	= err;
}

function unconfigureResources(properties, callback)
{
  try
  {
      console.log("----- Starting DELETE for " + TEMPLATE_PREFIX);
      async.series([

        deleteLexBot.bind(properties),

        function(error, res)
        {
          console.log("----- Ended Setup for " + TEMPLATE_PREFIX);
          console.log("----- With result data:" + JSON.stringify(g_resources));
          callback(null, g_resources);
        }
      ]);
  }
  catch (e)
  {
      console.log(e);
      callback("EXCEPTION::" + e.description, g_resources);
  }
  finally
  {

  }
}

function configureResources(properties, callback)
{
  try
  {
    var async = require('async');

    console.log("----- Starting Setup for " + TEMPLATE_PREFIX + " (Safe: " + STACKNAME_SAFE + ")");

    async.series([

      createLexBot.bind(properties),

      function(error, res)
      {
        callback(null, g_resources);
      }
      ]);
    }
    catch (e)
    {
        console.log(e);
        callback("EXCEPTION::" + e.description, g_resources);
    }
    finally
    {

    }
}

//
// sendResponse
//
function sendResponse(event, context, status, data, err)
{
  var reason = err ? err.message : '';
  var responseBody = {
    StackId: event.StackId,
    RequestId: event.RequestId,
    LogicalResourceId: event.LogicalResourceId,
    PhysicalResourceId: context.logStreamName,
    Status: status,
    Reason: reason + " See details in CloudWatch Log: " + context.logStreamName,
    Data: data
  };

  console.log("RESPONSE:\n", responseBody);
  var json = JSON.stringify(responseBody);

  var https = require("https");
  var url = require("url");

  var parsedUrl = url.parse(event.ResponseURL);
  var options = {
    hostname: parsedUrl.hostname,
    port: 443,
    path: parsedUrl.path,
    method: "PUT",
    headers: {
      "content-type": "",
      "content-length": json.length
    }
  };

  var request = https.request(options, function(response) {
    console.log("STATUS: " + response.statusCode);
    console.log("HEADERS: " + JSON.stringify(response.headers));
    context.done(null, data);
  });

  request.on("error", function(error) {
    console.log("sendResponse Error:\n", error);
    context.done(error);
  });

  request.on("end", function() {
    console.log("end");
  });
  request.write(json);
  request.end();
}

function deleteLexBot(next)
{
  console.log("deleteLexBot()")
  async.waterfall([
    GetBotStructure.bind(this),
    DeleteBotAlias.bind(this),
    DeleteBot.bind(this),
    DeleteIntents.bind(this)
  ],
  function(error, res)
  {
    if (error)
    {
        console.log("deleteLexBot - error occurred");
        console.log(error.message);
        next();
    }
    else
    {
        console.log("deleteLexBot - processed ok");
        next();
    }
  }
 );
}

function createLexBot(next)
{
  console.log("createLexBot()")
  async.waterfall([
    GetBotStructure.bind(this),
    CheckBot.bind(this),
    CheckIntents.bind(this),
    CreateIntents.bind(this),
    CreateAndBuiltBot.bind(this),
    WaitForBotToBuild.bind(this),
    CreateBotVersion.bind(this),
    CreateBotAlias.bind(this),
  ],
  function(error, res)
  {
    if (error)
    {
        console.log("createLexBot - error occurred");
        console.log(error.message);
        next();
    }
    else
    {
        console.log("createLexBot - processed ok");
        next();
    }
  }
 );
}

function WaitForBotToBuild(botStructure, next)
{
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("Waiting for bot to build... " + thisBotName);
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  var params =
  {
    name            : thisBotName,
    versionOrAlias  : "$LATEST"
  };

  var keepWaiting = true;
  var buildFailed = false;
  async.whilst(

      //
      // Test function
      //
      function()
      {
        return keepWaiting;
      },
      //
      // A function which is called each time the above test passes (returns true)
      //
      function(whilstCallback)
      {
        lexmodelbuildingservice.getBot(params, function(err, data)
        {
          if (err)
          {
            // Assume the Bot does not exist, that's why the error was thrown
            console.log("An error occurred - we need to fail here, can't continue");
            keepWaiting = false;
            buildFailed = true;
          }
          else
          {
            // The whilst control flow will keep going until we return a false
            if ( data.status == "BUILDING" )
            {
              console.log("Bot is building. Will sleep 5 seconds and then try again.");
              setTimeout(whilstCallback, 5000);
            }
            else
            if ( data.status == "READY" )
            {
              console.log("Bot is built! Giving things time to settle...");
              keepWaiting = false;
              setTimeout(whilstCallback, 10000);
            }
            else
            {
              console.log("Bot status is critical - " + data.status + " - Aborting.");
              keepWaiting = false;
              buildFailed = true;
              whilstCallback();
            }
          }
        })
      },
      //
      // callback which is called after the test function has returned false
      //
      function ()
      {
        if (buildFailed)
        {
          next("Bot Build Failed");
        }
        else
        {
          next(null, botStructure);
        }
      }
    );
}

function DeleteIntents(botStructure, next)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  async.eachSeries(
    Object.keys(botStructure.IntentDefinitions).map((key) => botStructure.IntentDefinitions[key]),
    function(intentDefinition, iterCallback)
    {
      console.log("Deleting Intent: " + STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_" + intentDefinition.name);

      lexmodelbuildingservice.deleteIntent(
        {
          name : STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_" + intentDefinition.name
        },
        function(err, data)
        {
          if( err )
          {
            console.log('Intent deletion failed for ' + intentDefinition.name);
            console.log(err.message)
            setTimeout(()=>{iterCallback();}, 5000);
          }
          else
          {
            console.log(intentDefinition.name + ' deleted successfully');
            setTimeout(()=>{iterCallback();}, 5000);
          }
        })
    },
    function(err)
    {
      next(err, botStructure);
    });
}

function DeleteBot(botStructure, next)
{
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("DeleteBot() for " + thisBotName);
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  var params =
  {
    nameContains: thisBotName
  };

  console.log("Deleting Bots like " + params.nameContains);
  lexmodelbuildingservice.getBots(params, function(err, data)
  {
    if (err)
    {
      // Assume the Bot does not exist, that's why the error was thrown
      console.log("An error occurred - unable to list bots");
      next(null, botStructure);
    }
    else
    {
      if ( data.bots.length == 0 )
      {
        console.log("Bot not found - continuing...");
        next(null, botStructure);
      }
      else
      if ( data.bots.length != 1 )
      {
        console.log("Found " + data.bots.length + " matching bots");
        console.log("Auto-delete of this bot will not continue, should only have found 1!!")
        next(null, botStructure);
      }
      else
      {
        lexmodelbuildingservice.deleteBot(
          {
            name      : thisBotName
          },
          function(err, data)
          {
            if (err)
            {
              // Assume the Bot does not exist, that's why the error was thrown
              console.log("An error occurred - unable to delete bot");
              console.log(err.message);
              next();
            }
            else
            {
              console.log("Bot deleted ok");
              setTimeout(()=>{next(null, botStructure);}, 5000);
            }
          });
      }

    }
  });
}

function GetBotStructure(next)
{
  var botDefinition =
  {
    BotName                 : "",
    IntentDefinitionFiles   :
    [
      "lex-intent-WhatsMyParameterIntent.json"
    ],
    IntentDefinitions :
    [
      // intentionally empty
    ]
  }

  //
  // Read in all the definitions
  botDefinition.IntentDefinitionFiles.forEach((filename)=>
  {
    var intentDefinition = fs.readFileSync(
      "./autoconfig/" + filename,
      "utf8"
      );
    intentDefinition = JSON.parse(intentDefinition);
    botDefinition.IntentDefinitions[intentDefinition.name] = intentDefinition;
  });

  console.log(botDefinition)

  //
  // Continue
  //
  next
  (
    null,
    botDefinition
  );
}

function CheckBot(botStructure, next)
{
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("CheckBot() for " + thisBotName);
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  var params =
  {
    nameContains: thisBotName
  };

  console.log("Getting Bots like " + params.nameContains);
  lexmodelbuildingservice.getBots(params, function(err, data)
  {
    if (err)
    {
      // Assume the Bot does not exist, that's why the error was thrown
      console.log("An error occurred - assume bot does not exist");
      next(null, botStructure);
    }
    else
    {
      if ( data.bots.length > 0 )
      {
        console.log("Found " + data.bots.length + " matching bots");
        console.log("Assuming the bot for this stack (" + thisBotName + ") is already created.")
        botStructure.BotName = thisBotName;
      }

      next(null, botStructure);
    }
  });
}

function CheckIntents(botStructure, next)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();
  var params =
  {
    nameContains: STACKNAME_SAFE
  };

  lexmodelbuildingservice.getIntents(params, function(err, data)
  {
    if( err )
    {
      console.log('getIntents failed to process - ' + err.message);
      next(err);
    }
    else
    {
      //console.log(data);
      if ( data.intents.length > 0 )
      {
        console.log('Found ' + data.intents.length + ' intents matching the Stack Name \'' + params.nameContains + "'");

        for ( var intent in data.intents )
        {
          var thisIntent = data.intents[intent];

          //
          // For each of the intents we found matching our name prefix,
          // remove from the list of intents we need to create
          //
          var intentName = thisIntent.name.replace(STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_", "");
          console.log("     Inspecting '" + intentName + "' (" + thisIntent.name + ")");
          if ( botStructure.IntentDefinitions[intentName] )
          {
            botStructure.IntentDefinitions[intentName].version = thisIntent.version;
            console.log("     - Set version to " + thisIntent.version);
          }
        }
      }

      next(null, botStructure);

    }
  });

}
function CreateIntents(botStructure, next)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  async.eachSeries(
    Object.keys(botStructure.IntentDefinitions).map((key) => botStructure.IntentDefinitions[key]),
    function(intentDefinition, iterCallback)
    {
      if ( !intentDefinition.version )
      {
        intentDefinition.name = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_" + intentDefinition.name;
        intentDefinition.fulfillmentActivity.codeHook.uri = intentDefinition.fulfillmentActivity.codeHook.uri.replace("REPLACE_WITH_LEXTBOTHANDLER_ARN", LEXBOTHANDLER_ARN);

        console.log("Creating Intent: " + intentDefinition.name);
        console.log("With Handler: " + intentDefinition.fulfillmentActivity.codeHook.uri);

        lexmodelbuildingservice.putIntent(intentDefinition, function(err, data)
        {
          if( err )
          {
            console.log('Intent create failed for ' + intentDefinition.name);
            console.log(err.message)
            iterCallback(err);
          }
          else
          {
            console.log(intentDefinition.name + ' created successfully');
            CreateIntentVersion(intentDefinition.name, botStructure, iterCallback);
          }
        })
      }
      else
      {
        console.log("     Skipping " + intentDefinition.name + " - version already set to " + intentDefinition.version);
        iterCallback();
      }
    },
    function(err)
    {
      next(err, botStructure);
    });
}

function CreateBotAlias(botStructure, callback)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("Publishing Bot Alias: " + thisBotName);

  lexmodelbuildingservice.putBotAlias(
    {
      botName     : thisBotName,
      botVersion  : "1",
      name        : "current"
    },
    function(err, data)
  {
    if( err )
    {
      console.log('Publish Bot failed for ' + thisBotName);
      console.log(err.message)
      callback(err);
    }
    else
    {
      console.log(thisBotName + ' alias published successfully');
      callback(null, botStructure);
    }
  });
}

function CreateIntentVersion(intentName, botStructure, callback)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();

  console.log("CreateIntentVersion() for: " + intentName);

  lexmodelbuildingservice.createIntentVersion(
    {
      name     : intentName
    },
    function(err, data)
  {
    if( err )
    {
      console.log('Create intent version failed for ' + intentName);
      console.log(err.message)
      callback(err);
    }
    else
    {
      console.log(intentName + ' version created successfully - version ' + data.version);
      var cleanIntentName = intentName.replace(STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_", "");
      botStructure.IntentDefinitions[cleanIntentName].version = data.version;
      callback();
    }
  });
}


function CreateBotVersion(botStructure, callback)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("Publishing Bot Version: " + thisBotName);

  lexmodelbuildingservice.createBotVersion(
    {
      name     : thisBotName
    },
    function(err, data)
  {
    if( err )
    {
      console.log('Publish Bot Version failed for ' + thisBotName);
      console.log(err.message)
      callback(err);
    }
    else
    {
      console.log(thisBotName + ' Version published successfully, waiting 5 seconds for things to settle');
      setTimeout(()=>{callback(null, botStructure);}, 5000);
    }
  });
}

function DeleteBotAlias(botStructure, callback)
{
  var lexmodelbuildingservice = new AWS.LexModelBuildingService();
  var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

  console.log("Deleting Bot Alias 'current' for: " + thisBotName);

  lexmodelbuildingservice.deleteBotAlias(
    {
      botName     : thisBotName,
      name        : "current"
    },
    function(err, data)
  {
    if( err )
    {
      console.log('Delete Bot alias failed for ' + thisBotName);
      console.log(err.message)
      console.log("Continuing anyway...");
    }
    else
    {
      console.log(thisBotName + ' alias deleted successfully');
    }
    setTimeout(()=>{callback(null, botStructure);}, 5000);
  });
}

function CreateAndBuiltBot(botStructure, callback)
{
  if ( botStructure.BotName == "" )
  {
    var lexmodelbuildingservice = new AWS.LexModelBuildingService();
    var thisBotName = STACKNAME_SAFE + "_" + RESOURCE_PREFIX + "_KeyValQuery";

    var botDefinition = require('fs').readFileSync(
      "./autoconfig/lex-bot-KeyValQuery.json",
      "utf8"
      );

    botDefinition = JSON.parse(botDefinition);
    botDefinition.name = thisBotName;
    console.log("Creating Bot: " + botDefinition.name);

    //
    // Build the array of intents
    //
    botDefinition.intents = [];
    for ( var definition in botStructure.IntentDefinitions )
    {
      var thisDefinition = botStructure.IntentDefinitions[definition];
      console.log("     Adding intent " + thisDefinition.name);
      botDefinition.intents.push(
      {
        intentName    : thisDefinition.name,
        intentVersion : thisDefinition.version
      });
    };

    lexmodelbuildingservice.putBot(botDefinition, function(err, data)
    {
      if( err )
      {
        console.log('Bot create failed for ' + botDefinition.name);
        console.log(err.message)
        callback(err);
      }
      else
      {
        console.log(botDefinition.name + ' created successfully');
        callback(null, botStructure);
      }
    });
  }
  else
  {
    callback(null, botStructure);
  }
}

function WriteBufferToS3(bufferToWrite, bucket, key, contentType, callback)
{
  var params = {
       Bucket         : bucket,
       Key            : key,

       ContentLength  : bufferToWrite.length,
       ContentType    : contentType,
       Body           : bufferToWrite
   };
   console.log("Writing buffer to " + bucket + "/" + key);
   var s3 = new AWS.S3();
   s3.putObject(params, (err, data)=>
   {
     if ( !err )
     {
       var url = s3.getSignedUrl(
         'getObject',
         {
           Bucket : bucket,
           Key    : key,
           Expires: 60 * 1000 * 60 * 24 * 7
         },
         (err, url)=>
         {
           callback(err, url);
         });
      }
      else
      {
          console.log("ERROR::WriteBufferToS3() -> " + err.message);
          callback(err);
      }
   });
}

function ReadPropertyBag(properties, callback)
{

  utils.DownloadFileFromS3(
      properties.S3WebHostingBucket,
      "$private/cfn_property_bag.json",
      "/tmp/cfn_property_bag.json",
      (err, filePath)=>
      {
        if (err)
        {
          console.log("ERROR::ReadPropertyBag() -> Could not read property bag, but will continue!");
          callback();
        }
        else
        {
          var propertyBag = require('fs').readFileSync(
        		"/tmp/cfn_property_bag.json",
        		"utf8"
        		);

          console.log("Property bag rehydrated ok");
          try
          {
            g_propertyBag = JSON.parse(propertyBag);
          }
          catch(ex){}

          callback();
        }
      }
    );

}

function WritePropertyBag(properties, callback)
{
  console.log("WritePropertyBag() -> $private/cfn_property_bag.json");

  WriteBufferToS3(
    JSON.stringify(g_propertyBag),
    properties.S3WebHostingBucket,
    "$private/cfn_property_bag.json",
    "application/json",
    (err, url)=>
    {
      if ( err )
      {
        console.log("ERROR::WritePropertyBag() -> " + err.message);
        callback();
      }
      else
      {
        console.log("$private/cfn_property_bag.json written ok");
        callback();
      }
    }
  );
}


function deleteBucketContent(next)
{
    console.log("Removing bucket contents...");

    var self  = this;
    var s3    = new AWS.S3();

    var params = {
        Bucket: self.S3WebHostingBucket
    };

  s3.listObjects(params, function(err, data)
  {

    if (err)
    {
        console.log("Bucket contents could not be deleted!");
        console.log(err);
        next();
    }
    else
    {

        if (data.Contents.length == 0)
        {
            console.log("Nothing to delete in bucket " + params.Bucket);
            next();
        }
        else
        {
            params = {
                Bucket: self.S3WebHostingBucket,
                Delete: {Objects:[]}
            };

            console.log("Start iteration of bucket contents:");
            data.Contents.forEach(function(content)
            {
                console.log("     " + content.Key);
                params.Delete.Objects.push({Key: content.Key});
            });

            s3.deleteObjects(params, function(err, data)
            {
                if (err)
                {
                    console.log("Bucket contents could not be deleted!");
                    console.log(err);
                    next();
                }
                else
                {
                    console.log("Bucket contents deleted OK");
                    next();
                }
            });
        };
  }});
}
