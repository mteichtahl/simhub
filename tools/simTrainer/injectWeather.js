'use strict'


var net = require('net');
var _ = require('lodash');
const color = require('cli-color');

var client = new net.Socket();


const coverage = ['Clear', 'Few', 'Scattered', 'Borken', 'Overcast'];
const windSeverity = ['Heavy', 'Moderate', 'Light', 'Light', 'None', 'Severe'];
const precipitationType = ['None', 'Rain', 'Snow', 'Hail', 'Freezing Rain'];

var command = {
  'command': 'weather',
  'parameters': {
    'altimeter': '1013',
    'temperature': '30',
    'dewpoint': '5',
    'cloud': [{
      'altitude': '2000',
      'coverage': 'Overcast',
      'cloud_type': 'Auto',
      'cloud_top': 'Round',
      'turbulence': 'Severe',
      'precipitation_type': 'None',
      'precipitation': 'Light',
      'icing': 'None'
    }],
    'wind': [{
      'altitude': '2000',
      'speed': '20',
      'gusting': '45',
      'severity': 'Severe',
      'shear': 'Gradual',
      'direction': '200'
    }],
    'station': 'GLOB',
    'visibility': '500'
  }
}

const config = {
  region: 'us-east-1',
  streamName: 'simTrain',
  simHost: '192.168.2.2',
  simPort: 8081,
  dynamoTable: 'simTrainer'
};

function send(json, cb) {
  var command = new Buffer.from(JSON.stringify(json) + '\n');
  client.write(command);
  cb();
}

client.connect(config.simPort, config.simHost, function() {
  var hasLanded = false;

  console.log(color.green(`Connected to ${config.simHost}:${config.simPort}`));

  send(command, function() {
    console.log('sent');
  });

}.bind(this))