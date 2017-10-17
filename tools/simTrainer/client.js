var net = require('net');

var client = new net.Socket();

var command = {
  command: 'approachJump',
  parameters: {translation: '5 miles final', airport: 'KJFK', runway: '04R'}
};

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

var poo = JSON.stringify(command);
console.log(poo);
var buf = new Buffer.from(poo, 'utf8');

client.connect(8091, '192.168.2.2', function() {
  console.log('Connected');
  client.write(buf, function(err, data) {
    console.log(JSON.stringify(command))

    console.log(err, data)
  })
  // client.write(JSON.stringify(command))

})
client.on('error', function(err) {
  console.log(err)
})
client.on('close', function() {
  console.log('Connection closed');
});
