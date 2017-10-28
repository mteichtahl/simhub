var net = require('net');
var sleep = require('sleep');
var _ = require('lodash');
var json2csv = require('json2csv');
const uuid = require('uuid/v4');
const color = require('cli-color');
var KinesisClient = require('./kinesisClient');
var DynamoClient = require('./dynamoClient');

var client = new net.Socket();

// flight state constants
const ON_GROUND_CRASHED = -1;
const FLYING = 0;
const ON_GROUND_LANDED = 1;
const ILS_LOST = 2;
const FLOAT_ACCURACY = 5;

const collectorId = uuid();
var approachCount = 0;
var rowCount = 0;

var json;
var kinesis = undefined;
var dynamo = undefined;

config = {
  region: 'us-east-1',
  streamName: 'simTrain',
  simHost: '192.168.2.2',
  simPort: 8081,
  dynamoTable: 'simTrainer'
}


var approach = {
  command: 'approachJump',
  parameters: {translation: '10 miles final', airport: 'KJFK', runway: '04R'}
};

var pause = {'command': 'pause', 'parameters': {'set': 'true'}};
var unpauseJSON = {'command': 'pause', 'parameters': {'set': 'false'}};

var autopilotJSON = {
  'command': 'autopilot',
  'parameters': {
    'altitude': '2000',
    'speed': '180',
    'modes': 'AT,CMD_A,SPEED,VS,HDG_SEL,APP'
  }
};

var autolandStartJSON = {
  'command': 'autoland',
  'parameters': {'mode': 'start'}
};

var autolandStopJSON = {'command': 'autoland', 'parameters': {'mode': 'stop'}};

var flightState = {ready: false, paused: false, status: undefined};



// var command = {
//   'command': 'weather',
//   'parameters': {
//     'altimeter': '1013',
//     'temperature': '15',
//     'dewpoint': '5',
//     'cloud': [{
//       'altitude': '0',
//       'coverage': 'Clear',
//       'cloud_type': 'Auto',
//       'cloud_top': 'Round',
//       'turbulence': 'None',
//       'precipitation_type': 'None',
//       'precipitation': 'Light',
//       'icing': 'None'
//     }],
//     'wind': [{
//       'altitude': '3000',
//       'speed': '20',
//       'gusting': '45',
//       'severity': 'None',
//       'shear': 'Gradual',
//       'direction': '200'
//     }],
//     'station': 'GLOB',
//     'visibility': '4000'
//   }
// }

var approachJump = new Buffer.from(JSON.stringify(approach) + '\n');
var pauseBuffer = new Buffer.from(JSON.stringify(pause) + '\n');
var unpause = new Buffer.from(JSON.stringify(unpauseJSON) + '\n');
var autopilot = new Buffer.from(JSON.stringify(autopilotJSON) + '\n');
var autolandStart = new Buffer.from(JSON.stringify(autolandStartJSON) + '\n');
var autolandStop = new Buffer.from(JSON.stringify(autolandStopJSON) + '\n');


var startRun = false;
var inPosition = false;
var hasCrashed = false;
var hasLanded = false;
var hasLostILS = false;



function simIsReadyForRepositioning() {
  return flightState.ready && !flightState.paused &&
      (flightState.status != FLYING);
}

function enableAutoPilot() {
  console.log(color.yellow(' -> Auto Pilot Set'))
  client.write(autopilot);
}

function enableAutoLand() {
  console.log(color.yellow(' -> Auto Land Set'));
  client.write(autolandStart);
}


function waitForPosition(cb) {
  console.log(color.yellow(` -> Starting approach ${approachCount}`));

  setTimeout(() => {
    client.write(unpause);
    console.log(color.yellow('Waiting for sim'));
  }, 15000);


  var interval = setInterval(function() {
    // check if reposition is complete
    if (flightState.ready && flightState.status == FLYING) {
      console.log(color.yellow(' -> Aircraft in position'));
      inPosition = true;
      clearInterval(interval);
      cb();
    }
  }, 1000)
}


function waitForSimReadyToReposition(cb) {
  var interval = setInterval(function() {
    if (simIsReadyForRepositioning()) {
      console.log(color.green('Simulator is ready'));
      startRun = true;
      clearInterval(interval);
      cb()
    }
  }, 1000)
}

function waitForLanding(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ON_GROUND_LANDED && !hasCrashed) {
      console.log(color.green(`Approach ${approachCount} landed successfully`));
      approachCount++;
      hasLanded = true;
      clearInterval(interval);
      cb()
    } else if (hasCrashed) {
      clearInterval(interval);
    }
  }, 1000)
}

function sendApproachDataToDynamo(jsonData) {
  var item = {
    'sts': {S: jsonData.data.sts},
    'collectorId': {S: collectorId},
    'runNumber': {S: approachCount.toString()},
    'rowCount': {S: rowCount.toString()},
    'result': {S: jsonData.outcome}
  };

  dynamo.writeItem(item, function(err, data) {
    if (err) {
      console.log(color.red(err, err.stack));
    }  // an error occurred
    else {
      console.log(color.green(`Written approach ${approachCount} to Dynamo`));
    }
  });
  rowCount = 0;
}

function waitForCrash(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ON_GROUND_CRASHED) {
      console.log(color.red(`Approach ${approachCount} Crashed`));
      approachCount++;
      hasCrashed = true;
      clearInterval(interval);
      cb()
    } else if (hasLanded) {
      clearInterval(interval);
    }
  }, 500)
}

function waitForILSLost(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ILS_LOST) {
      console.log(color.red(`Approach ${approachCount} lost ILS`));
      approachCount++;
      hasLostILS = true;
      inPosition = false;
      clearInterval(interval);
      cb()
    } else if (hasLanded || hasCrashed) {
      clearInterval(interval);
    }
  }, 500)
}

function start() {
  startRun = false;
  inPosition = false;
  hasCrashed = false;
  hasLanded = false;
  hasLostILS = false;

  waitForSimReadyToReposition(function() {
    if (startRun && !inPosition) {
      client.write(approachJump);
      startRun = false;
      waitForPosition(function() {
        enableAutoPilot();
        enableAutoLand();
        console.log(color.blink.yellow('Waiting for approach to complete...'));

        waitForLanding(function() {
          json.outcome = 'Land';
          sendApproachDataToDynamo(json);
          client.write(autolandStop);
          start();
        })

        waitForCrash(function() {
          json.outcome = 'Crash';
          sendApproachDataToDynamo(json);
          client.write(autolandStop);
          start();
        })

        waitForILSLost(function() {
          json.outcome = 'ILS';
          sendApproachDataToDynamo(json);
          client.write(autolandStop);
          start();
        })


      })
    }
  }.bind(this));
}

function processSimDataForKinesis(sim) {
  sim.collectorId = collectorId;
  sim.runId = `${approachCount}`;
  sim.data.pitch = sim.data.pitch.toFixed(FLOAT_ACCURACY);
  sim.data.roll = sim.data.roll.toFixed(FLOAT_ACCURACY);
  sim.data.yaw = sim.data.yaw.toFixed(FLOAT_ACCURACY);
  sim.data.airspeed = sim.data.airspeed.toFixed(FLOAT_ACCURACY);
  sim.data.altitude = sim.data.altitude.toFixed(FLOAT_ACCURACY);
  sim.data.vspeed = sim.data.vspeed.toFixed(FLOAT_ACCURACY);
  sim.data.weather.wind.heading =
      sim.data.weather.wind.heading.toFixed(FLOAT_ACCURACY);
  sim.data.weather.temp = sim.data.weather.temp.toFixed(FLOAT_ACCURACY);

  var loc = sim.data.ilsDeviation.loc;
  var gs = sim.data.ilsDeviation.gs;

  typeof loc != 'string' ? loc = loc.toFixed(FLOAT_ACCURACY) : loc = -2.5;
  typeof gs != 'string' ? gs = gs.toFixed(FLOAT_ACCURACY) : gs = -2.5;
  sim.data.ilsDeviation.loc = loc;
  sim.data.ilsDeviation.gs = gs;

  var output = json2csv(
      {data: sim, hasCSVColumnTitle: false, flatten: true, newLine: '\r\n'});
  output += '\n';
  return output;
}


client.connect(config.simPort, config.simHost, function() {
  console.log(color.green(`Connected to ${config.simHost}:${config.simPort}`));
  kinesis = new KinesisClient(config.region, config.streamName);
  dynamo = new DynamoClient(config.region, config.dynamoTable);

  console.log(color.blueBright('\nWaiting for simulator.....'));
  var hasLanded = false;

  start();
})

client.on('error', function(err) {
  console.log(err)
})
client.on('close', function() {
  console.log('Connection closed');
});
client.on('data', function(data) {
  try {
    json = JSON.parse(data.toString());

  } catch (e) {
    process.stdout.write('e');
    return;
  }

  if (json.result != undefined) {
    if (json.result == 'fail' || json.result == 'error') {
      console.log(json);
    }
  }

  if (json.data !== undefined) {
    flightState.paused = json.data.paused;
    flightState.ready = json.data.ready;
    flightState.status = json.data.status;

    var kinesisData = processSimDataForKinesis(json);
    if (!json.data.paused || !json.data.ready) {
      kinesis.write(kinesisData, function(ret) {});
    }

    switch (json.data.status) {
      case ON_GROUND_CRASHED:
        flightState.statusText = 'ON_GROUND_CRASHED'
        break;
      case FLYING:
        flightState.statusText = 'FLYING'
        break;
      case ON_GROUND_LANDED:
        flightState.statusText = 'ON_GROUND_LANDED'
        break;
      case ILS_LOST:
        flightState.statusText = 'ILS_LOST'
        break;
      default:
        flightState.statusText = 'UNKNOWN'
    }
  }

  rowCount++;

})
