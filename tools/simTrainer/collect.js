'use strict'

var color = require('cli-color')
var cli = require('commander')
var net = require('net')
var _ = require('lodash')
var aws = require('aws-sdk')

var totalRecordCount = 0;
var intervalRecordCount = 0;
var firstRecord = true;

cli.version('1.0.0')
  .usage('[options]')
  .option('-h, --host [type]', 'IP or name of the server', 'localhost')
  .option('-p --port [8080]', 'TCP Port', '8080')
  .parse(process.argv)

console.log(color.green(`Starting training data collection for ${cli.host} port ${cli.port}`))

var dataStream = net.createConnection(cli.port, cli.host)

dataStream
  .on('error', function (error) {
    console.log(color.red(`${error}`))
  })
  .on('connect', function () {
    console.log(color.green(`Connected to ${cli.host}:${cli.port}`))

    setInterval(function (a) {
      console.log(color.yellow(`Processing: ${intervalRecordCount}/${totalRecordCount}`))
      intervalRecordCount = 0;
    }, 5000)
  })
  .on('data', function (data) {
    if (firstRecord)
      console.log(color.yellow(`Receiving data`))

    var jsonData = JSON.parse(data.toString());
    totalRecordCount++
    intervalRecordCount++
    firstRecord = false

  })