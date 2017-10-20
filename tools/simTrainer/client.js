var net = require('net');
var sleep = require('sleep');

var client = new net.Socket();

var approach = {
  command: 'approachJump',
  parameters: {translation: '10 miles final', airport: 'KJFK', runway: '04R'}
};

var pause = {'command': 'pause', 'parameters': {'set': 'true'}};
var unpauseJSON = {'command': 'pause', 'parameters': {'set': 'false'}};


var autopilot = {
  'command': 'autopilot',
  'parameters': {
    'altitude': '5000',
    'speed': '180',
    'modes': 'AT,CMD_A,SPEED,VS,HDG_SEL,APP'
  }
};

var autoland = {'command': 'autoland', 'parameters': {'mode': 'start'}};

var flightState = {'ready': false, 'paused': false};



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

client.connect(8081, '192.168.2.2', function() {
  console.log('\nConnected');

  //   if (!flightState.paused) {
  //     setTimeout(function() {
  //       client.write(pauseBuffer);
  //       console.log('\nPaused');
  //     }, 3000);
  //   }

  setTimeout(function() {
    console.log('\nApproach');
    client.write(approachJump);


    var readyInterval = setInterval(function() {
      console.log(flightState);
      client.write(unpause);

      if (flightState.ready) {
        console.log('\nAutopilot');
        client.write(autopilotBuffer);

        console.log('\nAuto land');
        client.write(autolandBuffer);

        client.write(unpause);
        clearInterval(readyInterval);
      }
    }, 1000)

  }, 500)


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
    // process.stdout.write('d');

  } catch (e) {
    process.stdout.write('e');
    // var str = '';
    // for (var ii = 0; ii < data.length; ii++) {
    //   str += data[ii].toString(16) + ' ';
    // };
    // console.log('--\n');
    // console.log(e)
    // // console.log(str + '\n--\n');
    // console.log(data.toString());
    // console.log('\n------------\n');
    return;
  }
  //   console.log(json.data.readay ? "rr");

  if (json.result != undefined) {
    if (json.result == 'fail' || json.result == 'success') {
      console.log('\n', json);
    }
  }

  if (json.data !== undefined) {
    flightState.paused = json.data.paused;
    flightState.ready = json.data.ready;
  }

})
