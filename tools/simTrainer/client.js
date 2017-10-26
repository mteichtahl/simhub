var net = require('net');
var sleep = require('sleep');

var client = new net.Socket();

const ON_GROUND_CRASHED = -1;
const FLYING = 0;
const ON_GROUND_LANDED = 1;
const ILS_LOST = 2;


var approach = {
  command: 'approachJump',
  parameters: {translation: '5 miles final', airport: 'KJFK', runway: '04R'}
};

var pause = {'command': 'pause', 'parameters': {'set': 'true'}};
var unpauseJSON = {'command': 'pause', 'parameters': {'set': 'false'}};

var autopilot = {
  'command': 'autopilot',
  'parameters': {
    'altitude': '2000',
    'speed': '180',
    'modes': 'AT,CMD_A,SPEED,VS,HDG_SEL,APP'
  }
};

var autoland = {'command': 'autoland', 'parameters': {'mode': 'start'}};

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
var autopilotBuffer = new Buffer.from(JSON.stringify(autopilot) + '\n');
var autolandBuffer = new Buffer.from(JSON.stringify(autoland) + '\n');

function simIsReady() {
  return flightState.ready && !flightState.paused &&
      flightState.status == ON_GROUND_LANDED;
}

var startRun = function() {


  console.log('Waiting for start state');

  // console.log('\nApproach');
  // client.write(approachJump);

  // let index = 0;
  // var readyInterval = setInterval(function() {


  //   if (flightState.paused && index == 0) {
  //     client.write(unpause);

  //     console.log(index++);
  //   }

  //   if (flightState.ready) {
  //     console.log('\nAutopilot');
  //     client.write(autopilotBuffer);

  //     console.log('\nAuto land');
  //     client.write(autolandBuffer);

  //     client.write(unpause);
  //     clearInterval(readyInterval);
  //   }
  // }.bind(this), 1000);

};

function waitForPosition(cb) {
  var interval = setInterval(function() {
    // check if reposition is complete
    if (flightState.ready && !flightState.paused &&
        flightState.status == FLYING) {
      clearInterval(interval);
      cb();
    }
  }.bind(this), 1000)
}


client.connect(8081, '192.168.2.2', function() {
  console.log('\nConnected');
  var startRun = false;
  var inPosition = false;

  var readyInterval = setInterval(
      function() {

        if (simIsReady()) {
          console.log('Ready for run');
          startRun = true;
          clearInterval(readyInterval);
        }
      }.bind(this),
      1000)


      var runInterval = setInterval(function() {
        if (startRun && !inPosition) {
          // reposition for approach
          client.write(approachJump);
          inPosition = true;

          // setTimeout(function() {

          // }.bind(this), 2500)

          waitForPosition(function() {
            console.log('Positioned for run')
            client.write(autopilotBuffer);

            console.log('Auto Pilot Set')

            client.write(autolandBuffer);
            console.log('Auto Land Set')

            client.write(unpause);
            startRun = false;
          })
        }

        if (flightState.status == ON_GROUND_LANDED && !startRun) {
          console.log('landed');
        }

        if (flightState.status == ON_GROUND_CRASHED && !startRun) {
          console.log('crashed');
        }

      }.bind(this), 500)



})

client.on('error', function(err) {
  console.log(err)
})
client.on('close', function() {
  console.log('Connection closed');
});
client.on('data', function(data) {
  var json;
  try {
    json = JSON.parse(data.toString());

  } catch (e) {
    process.stdout.write('e');
    return;
  }

  if (json.result != undefined) {
    if (json.result == 'fail') {
      console.log('\n', json);
    }
  }

  if (json.data !== undefined) {
    flightState.paused = json.data.paused;
    flightState.ready = json.data.ready;
    flightState.status = json.data.status;

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
    // console.log(flightState);
  }

})
