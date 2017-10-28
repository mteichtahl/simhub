'use strict'

// "ready","paused","onGround","crashed","sts","ts","pitch","roll","yaw","airspeed","altitude","vspeed","ilsDeviation.loc","ilsDeviation.gs","onTrack","status","lng","lat","weather.wind.heading","weather.wind.speed","weather.temp","weather.turbulance","collectorId","runId"

var color = require('cli-color');
var cli = require('commander');
var net = require('net');
var _ = require('lodash');
var AWS = require('aws-sdk');
var json2csv = require('json2csv');
const uuid = require('uuid/v4');

var totalRecordCount = 0
var intervalRecordCount = 0
var firstRecord = true

const collectorId = uuid();
const runId = uuid();
let runCounter = 0
let runDataCount = 0;
let incrementRun = true;

const FLOAT_ACCURACY = 5;
// flight state constants
const ON_GROUND_CRASHED = -1;
const FLYING = 0;
const ON_GROUND_LANDED = 1;
const ILS_LOST = 2;


AWS.config = {
  region: 'us-east-1'
  // other service API versions
}

var kinesis = new AWS.Firehose();
var kinesisPartition = 0;
const partitionCount = 3;

var dynamodb = new AWS.DynamoDB();

function getPartition() {
  if (kinesisPartition < partitionCount) {
    return kinesisPartition.toString();
  }
  kinesisPartition++;
}

cli.version('1.0.0')
    .usage('[options]')
    .option(
        '-h, --host <name or IP>', 'IP or name of the server', '192.168.2.2')
    .option('-p, --port <port>', 'TCP Port', '8081')
    .option('-s, --streamName <name>', 'Kinesis stream name', 'simTrain')
    .option('-f, --format [csv,json]', 'Output type (csv or json)', 'csv')
    .option('-k, --kinesis [true, false]', 'Send to kinesis', true)
    .option('-d, --dynamo [true, false', 'Send tracking data to dynamo', true)
    .parse(process.argv)

console.log(color.green(
    `Starting training data collection for ${cli.host} port ${cli.port}`));
console.log(color.green(`collector id ${collectorId}`));

var dataStream = net.createConnection(cli.port, cli.host);

dataStream
    .on('error',
        function(error) {
          console.log(color.red(`${error}`));
        })
    .on('connect',
        function() {
          console.log(color.green(`Connected to ${cli.host}:${cli.port}`))

          setInterval(function(a) {
            console.log(color.yellow(
                `Processing: ${intervalRecordCount}/${totalRecordCount}`));
            intervalRecordCount = 0;
          }, 5000);
        })
    .on('data', function(data) {
      var jsonData = JSON.parse(data.toString());

      if (firstRecord) {
        // console.log(color.yellow(`Receiving data`));
      }


      if (jsonData.data.ready == false || jsonData.data.paused == true) {
        if (incrementRun)
          console.log(color.red(`Skipping while sim resetting...`));
        incrementRun = false;
        return;
      } else {
        incrementRun = true;
      }


      jsonData['data']['collectorId'] = collectorId;
      jsonData['data']['runId'] = `${runId}_${runCounter}`;
      jsonData['data']['pitch'] =
          jsonData['data']['pitch'].toFixed(FLOAT_ACCURACY);
      jsonData['data']['roll'] =
          jsonData['data']['roll'].toFixed(FLOAT_ACCURACY);
      jsonData['data']['yaw'] = jsonData['data']['yaw'].toFixed(FLOAT_ACCURACY);
      jsonData['data']['airspeed'] =
          jsonData['data']['airspeed'].toFixed(FLOAT_ACCURACY);
      jsonData['data']['altitude'] =
          jsonData['data']['altitude'].toFixed(FLOAT_ACCURACY);
      jsonData['data']['vspeed'] =
          jsonData['data']['vspeed'].toFixed(FLOAT_ACCURACY);

      if (typeof jsonData['data']['ilsDeviation']['loc'] != 'string')
        jsonData['data']['ilsDeviation']['loc'] =
            jsonData['data']['ilsDeviation']['loc'].toFixed(FLOAT_ACCURACY);
      else
        jsonData['data']['ilsDeviation']['loc'] = -2.5;

      if (typeof jsonData['data']['ilsDeviation']['gs'] != 'string')
        jsonData['data']['ilsDeviation']['gs'] =
            jsonData['data']['ilsDeviation']['gs'].toFixed(FLOAT_ACCURACY);
      else
        jsonData['data']['ilsDeviation']['gs'] = -2.5;

      jsonData['data']['weather']['wind']['heading'] =
          jsonData['data']['weather']['wind']['heading'].toFixed(
              FLOAT_ACCURACY);

      jsonData['data']['weather']['temp'] =
          jsonData['data']['weather']['temp'].toFixed(FLOAT_ACCURACY);

      // console.dir(jsonData, {depth: null});



      if (jsonData.data.status == ON_GROUND_CRASHED ||
          jsonData.data.status == ON_GROUND_LANDED ||
          jsonData.data.status == ILS_LOST && incrementRun) {
        console.log(color.yellow(`run ${runCounter}/${runDataCount} rows`));

        var params = {
          Item: {
            'sts': {S: jsonData.data.sts},
            'collectorId': {S: collectorId},
            'runNumber': {S: runCounter.toString()},
            'rowCount': {S: runDataCount.toString()}
          },
          ReturnConsumedCapacity: 'TOTAL',
          TableName: 'simTrainer'
        };

        if (runDataCount > 1 && cli.dynamo)
          dynamodb.putItem(params, function(err, data) {
            if (err)
              console.log(err, err.stack);  // an error occurred
            else
              console.log(data);
          });


        incrementRun = false;
        runCounter++
        runDataCount = 0
        console.log(color.yellow(` - New run: ${runCounter}`))
      }

      if (cli.kinesis) {
        var output = ''
        if (cli.format == 'csv') {
          output = json2csv({
            data: jsonData.data,
            hasCSVColumnTitle: false,
            flatten: true,
            newLine: '\r\n'
          });
          output += '\n';
          // console.log(output);
        }
        else {
          output = JSON.stringify(jsonData);
        }

        // console.log(output);
        var params = {
          Record: {Data: output},
          DeliveryStreamName: cli.streamName
        };


        kinesis.putRecord(params, function(err, data) {
          if (err) {
            console.log(err.message);
          }  // an error occurred
          else {
            console.log(color.green(` - written to kinesis`))
          }
        })
      }

      totalRecordCount++
      runDataCount++
      intervalRecordCount++
      firstRecord = false
    })
