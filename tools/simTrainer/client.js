var net = require('net');
var sleep = require('sleep');

var client = new net.Socket();

var approach = {
  command: 'approachJump',
  parameters: {translation: '5 miles final', airport: 'KJFK', runway: '04R'}
};

var pause = {'command': 'pause', 'parameters': {'set': 'true'}};

var autopilot = {
  'command': 'autopilot',
  'parameters': {
    'altitude': '2000',
    'speed': '200',
    'modes': 'SPEED,VS,HDG_SEL,APP,AT,CMD_A'
  }
};

var autoland = {'command': 'autoland', 'parameters': {'mode': 'start'}};

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

var approachBuffer = new Buffer.from(JSON.stringify(approach) + '\n');
var pauseBuffer = new Buffer.from(JSON.stringify(pause) + '\n');
var autopilotBuffer = new Buffer.from(JSON.stringify(autopilot) + '\n');
var autolandBuffer = new Buffer.from(JSON.stringify(autoland) + '\n');

client.connect(8081, '192.168.2.2', function() {
  console.log('Connected');
  client.write(approachBuffer);

  console.log('pause');

  setTimeout(function() {
    // client.write(pauseBuffer);
    // sleep.sleep(5);
    client.write(autopilotBuffer);
    sleep.sleep(5);
    client.write(autolandBuffer);
  }, 1000)


})

client.on('error', function(err) {
  console.log(err)
})
client.on('close', function() {
  console.log('Connection closed');
});
client.on('data', function(data) {
  var json = JSON.parse(data.toString());
  if (json.result != undefined) {
    console.log(json);
    if (json.result == 'fail' || json.result == 'success') {
      // client.destroy();
    }
  }

})
