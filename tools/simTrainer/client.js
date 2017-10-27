var net = require('net');
var sleep = require('sleep');

var client = new net.Socket();

// flight state constants
const ON_GROUND_CRASHED = -1;
const FLYING = 0;
const ON_GROUND_LANDED = 1;
const ILS_LOST = 2;


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

function isInPosition() {}

function enableAutoPilot() {
  console.log('Auto Pilot Set')
  client.write(autopilot);
}

function enableAutoLand() {
  console.log('Auto Land Set')
  client.write(autolandStart);
}


function waitForSimReadyToReposition(cb) {
  var interval = setInterval(function() {
    if (simIsReadyForRepositioning()) {
      console.log('Simulator is ready');
      startRun = true;
      clearInterval(interval);
      cb()
    }
  }, 1000)
}


function waitForPosition(cb) {
  console.log('Positioning aircraft.....');

  setTimeout(() => {
    client.write(unpause);
    console.log('Unpausing simulator....');
  }, 15000);


  var interval = setInterval(function() {
    // check if reposition is complete
    if (flightState.ready && flightState.status == FLYING) {
      console.log('Aircraft in position');
      inPosition = true;
      clearInterval(interval);
      cb();
    }
  }, 1000)
}

function waitForLanding(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ON_GROUND_LANDED && !hasCrashed) {
      console.log('landed')
      hasLanded = true;
      clearInterval(interval);
      cb()
    } else if (hasCrashed) {
      clearInterval(interval);
    }
  }, 1000)
}

function waitForCrash(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ON_GROUND_CRASHED) {
      console.log('crashed')
      hasCrashed = true;
      clearInterval(interval);
      cb()
    } else if (hasLanded) {
      clearInterval(interval);
    }
  }, 1000)
}

function waitForILSLost(cb) {
  var interval = setInterval(function() {
    if (flightState.status == ILS_LOST) {
      console.log('ils lost')
      hasLostILS = true;
      inPosition = false;
      clearInterval(interval);
      cb()
    } else if (hasLanded || hasCrashed) {
      clearInterval(interval);
    }
  }, 1000)
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
        console.log('running......');

        waitForLanding(function() {
          client.write(autolandStop);
          start();
        })

        waitForCrash(function() {
          client.write(autolandStop);
          start();
        })

        waitForILSLost(function() {
          client.write(autolandStop);
          start();
        })


      })
    }
  }.bind(this));
}


client.connect(8081, '192.168.2.2', function() {
  console.log('\nConnected');
  console.log('Waiting for simulator.....');
  var hasLanded = false;

  start();


  //   if ((flightState.status == ON_GROUND_LANDED) && !startRun) {
  //     if (!hasLanded) {
  //       console.log('landed');
  //       client.write(autolandStop);
  //       console.log('Auto Land Cleared');
  //       hasLanded = true;
  //     }
  //   }

  //   if ((flightState.status == ON_GROUND_CRASHED) && !startRun) {
  //     console.log('crashed');
  //   }



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
    if (json.result == 'fail' || json.result == 'error') {
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
