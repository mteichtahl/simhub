var color = require('cli-color');
var cli = require('commander');
var net = require('net');
var _ = require('lodash');

var DATA_INTERVAL_MS = 500;

var indicators = [
  // values are only 0 or 1
  'I_OH_SPEED_TRIM', 'I_OH_STDBY_POWER_OFF', 'I_OH_SOURCE_OFF1',
  'I_OH_SOURCE_OFF2', 'I_MC_FUEL', 'I_MC_HYDRAULICS', 'I_MC_DOORS'
];

var analogs = [
  // values are 0 - 255
  'A_ASP_ADF_1_VOLUME', 'A_ASP_ADF_2_VOLUME', 'A_ASP_MARKER_VOLUME',
  'A_CDU1_BRIGHTNESS', 'A_CDU2_BRIGHTNESS', 'R_XPDR', 'R_XPDR2'
];


var gauges = [
  // floats
  'G_OH_TEMPERATURE', 'G_OH_FUEL_TEMP', 'G_PED_RUDDER_TRIM', 'G_THROTTLE_LEFT',
  'G_THROTTLE_RIGHT'
]

cli.version('1.0.0')
    .usage('[options]')
    .option('-p --port [8080]', 'TCP Port', '8080')
    .parse(process.argv);

console.log(color.green(`Starting emulator on port ${cli.port}`));

var server = net.createServer();
server.on('connection', handleConnection);

server.listen(cli.port, () => {
  var address = server.address().address;
  var port = server.address().port;
});

function handleConnection(conn) {
  var self = this;
  var address = conn.remoteAddress;
  var port = conn.remotePort;
  var intervalTimer;

  console.log(color.yellow(`Client connected - ${address}:${port}`));

  conn.once('close', onConnClose);
  conn.once('error', onConnError);

  function onConnError(err) {
    console.log('Connection %s error: %s', remoteAddress, err.message);
  };

  function onConnClose() {
    console.log(color.yellow(`Client disconnect - ${address}:${port}`));
    clearInterval(intervalTimer);
  }

  intervalTimer = setInterval(
      (a) => {
        getData(a, conn);
      },
      DATA_INTERVAL_MS,
      {'indicators': indicators, 'analog': analogs, 'gauges': gauges}, conn);

  function getData(data, conn) {
    var indicatorCount = _.random(0, data.indicators.length - 1);
    var analogCount = _.random(0, data.analog.length - 1);
    var gaugesCount = _.random(0, data.gauges.length - 1);

    var indicatorValue = ['ON', 'OFF'];
    var outString = '';

    for (var i = 0; i < indicatorCount; i++) {
      var ind = data.indicators[_.random(0, data.indicators.length - 1)];
      var value = indicatorValue[_.random(0, 1)];
      outString += (`${ind} = ${value}\n`);
    }

    for (var i = 0; i < analogCount; i++) {
      var ind = data.analog[_.random(0, data.analog.length - 1)];
      var value = _.random(0, 255);
      outString += (`${ind} = ${value}\n`);
    }

    for (var i = 0; i < gaugesCount; i++) {
      var ind = data.gauges[_.random(0, data.gauges.length - 1)];
      var value = _.random(500, true);
      outString += (`${ind} = ${value}\n`);
    }

    conn.write(outString + '\n');
  }
}
