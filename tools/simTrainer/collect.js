'use strict'

var color = require('cli-color')
var cli = require('commander')
var net = require('net')
var _ = require('lodash')

cli.version('1.0.0')
  .usage('[options]')
  .option('-h, --host [type]', 'IP or name of the server', 'localhost')
  .option('-p --port [8091]', 'TCP Port', '8091')
  .parse(process.argv)

console.log(color.green(`Starting training data collection for ${cli.host} port ${cli.port}`))

var dataStream = net.createConnection(cli.port, cli.host)

dataStream
  .on('error', function (error) {
    console.log(color.red(`${error}`))
  })
  .on('connect', function () {
    console.log(color.green(`Connected to ${cli.host}:${cli.port}`))
  })
  .on('data', function (data) {
    console.log(data)
  })
