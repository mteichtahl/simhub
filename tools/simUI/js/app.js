const API_URL = '<INSERT_API_GATEWAY_URL_HERE>'

const MQTT_ENDPOINT = '10.10.10.3'
const MQTT_ENDPOINT_PORT = 1884
const MQTT_TOPIC = '/flight/predicted'
// const MQTT_TOPIC = '/#'

const MAX_HISTORY = 60
const FREQ = 1

var interval = 1000 / FREQ
var map
var marker
var mqttClient
var documentReady = false

var attitudeInstrument
var headingInstrument
var variometerInstrument
var airspeedInstrument
var altimeterInstrument

var dataHistory = {
  airspeed: new CBuffer(MAX_HISTORY),
  altitude: new CBuffer(MAX_HISTORY),
  heading: new CBuffer(MAX_HISTORY),
  pitch: new CBuffer(MAX_HISTORY),
  roll: new CBuffer(MAX_HISTORY),
  yaw: new CBuffer(MAX_HISTORY),
  lat: new CBuffer(MAX_HISTORY),
  lng: new CBuffer(MAX_HISTORY),
  vspeed: new CBuffer(MAX_HISTORY),
  prediction: new CBuffer(MAX_HISTORY),
  timestamp: undefined
}

var setOnTrackIndicatorColor = function (val) {
  if (val != 0) {
    $('#onTrackIndicator').css('background', '#00FF00')
  } else {
    $('#onTrackIndicator').css('background', '#FF0000')
  }
}

var getAverageOnTrackPercentage = function () {
  var samples = dataHistory.onTrack.size()

  var total = 0
  dataHistory.onTrack.forEach(function (el) {
    total += el
  })

  return (total / samples).toFixed(2)
}

var processMQTT = function (data) {
  var heading = parseFloat(data.heading.true).toFixed(2)
  var airspeed = parseFloat(data.airspeed).toFixed(2)
  var pitch = parseFloat(data.pitch).toFixed(2)
  var roll = parseFloat(data.roll).toFixed(2)
  var yaw = parseFloat(data.yaw).toFixed(2)
  var altitude = parseFloat(data.altitude).toFixed(0)
  var lat = parseFloat(data.lat)
  var lng = parseFloat(data.lng)
  var vs = parseFloat(data.vspeed).toFixed(2)
  var prediction = data.predicted

  dataHistory.airspeed.push(airspeed)
  dataHistory.altitude.push(altitude)
  dataHistory.heading.push(heading)
  dataHistory.lat.push(lat)
  dataHistory.lng.push(lng)
  dataHistory.pitch.push(pitch)
  dataHistory.roll.push(roll)
  dataHistory.yaw.push(yaw)
  dataHistory.vspeed.push(vs)
  dataHistory.prediction.push(prediction)
  dataHistory.timestamp = data.sts.S
}

client = new Paho.MQTT.Client(MQTT_ENDPOINT, MQTT_ENDPOINT_PORT, 'clientId')

client.connect({
  onSuccess: function () {
    console.log('connected')
    client.subscribe(MQTT_TOPIC, { qos: 0 })
  },
  onFailure: function (res) {
    console.log(res)
  }
})

var updateMapPostion = function () {
  map.setCenter(
    dataHistory.lat.last(), dataHistory.lng.last(),
    function () {
      marker = map.createMarker({
        lat: dataHistory.lat.last(),
        lng: dataHistory.lng.last(),
        title: 'test'
      })
      map.addMarker(marker)
    })
}

client.onMessageArrived = function (msg) {
  var data = JSON.parse(msg.payloadString)
  processMQTT(data)
  console.log(data)

  if (documentReady) {
    updateMapPostion()
    setOnTrackIndicatorColor(dataHistory.prediction.last())
    updateSparkLines()
    updateInstruments()
    updateText()
  }
}

client.onConnectionLost = function (responseObject) {
  console.log('connection lost: ' + responseObject.errorMessage)
}

var updateSparkLines = function () {
  $('#airspeedSparkline')
    .sparkline(dataHistory.airspeed.toArray(), {
      type: 'line',
      width: '90%',
      height: '45px',
      fillColor: '#FFFFFF'
    })
  $('#rollSparkline')
    .sparkline(dataHistory.roll.toArray(), {
      type: 'line',
      width: '90%',
      height: '10px',
      fillColor: '#FFFFFF'
    })
  $('#pitchSparkline')
    .sparkline(dataHistory.pitch.toArray(), {
      type: 'line',
      width: '90%',
      height: '10px',
      fillColor: '#FFFFFF'
    })

  $('#altitudeSparkline')
    .sparkline(dataHistory.altitude.toArray(), {
      type: 'line',
      width: '90%',
      height: '45px',
      fillColor: '#FFFFFF'
    })

  $('#headingSparkline')
    .sparkline(dataHistory.heading.toArray(), {
      type: 'line',
      width: '90%',
      height: '45px',
      fillColor: '#FFFFFF'
    })
}

var updateInstruments = function updateInstruments () {
  attitudeInstrument.setPitch(dataHistory.pitch.last())
  attitudeInstrument.setRoll(dataHistory.roll.last())
  headingInstrument.setHeading(dataHistory.heading.last())
  airspeedInstrument.setAirSpeed(dataHistory.airspeed.last())
  altimeterInstrument.setAltitude(dataHistory.altitude.last())
}

var updateText = function () {
  $('#headingText').text(dataHistory.heading.last())
  $('#airspeedText').text(dataHistory.airspeed.last())
  $('#altitudeText').text(dataHistory.altitude.last())
  $('#atitudeText').text(
    `${dataHistory.pitch.last()}/${dataHistory.roll.last()}`
  )
  $('#timeStamp')
    .text(moment(dataHistory.timestamp)
      .format('hh:mm:ss.m ddd DD/MM/YYYY'))
}

$(document)
  .ready(function () {
    $.support.cors = true

    attitudeInstrument = $.flightIndicator(
      '#attitude', 'attitude', {
        roll: 50,
        pitch: -20,
        size: 200,
        showBox: false
      })
    headingInstrument = $.flightIndicator(
      '#heading', 'heading', {
        heading: 0,
        showBox: false
      })
    variometerInstrument = $.flightIndicator(
      '#variometer', 'variometer', {
        vario: 0,
        showBox: true
      })
    airspeedInstrument = $.flightIndicator(
      '#airspeed', 'airspeed', {
        airspeed: 0,
        showBox: false
      })
    altimeterInstrument = $.flightIndicator(
      '#altimeter', 'altimeter', {
        altitude: 0,
        showBox: false
      })

    map = new GMaps({
      el: '#locationMap',
      lat: -12.043333,
      lng: -77.028333,
      zoom: 11
    })

    $('#airspeedSparkline')
      .sparkline([], {
        type: 'line',
        width: '90%',
        height: '45px',
        fillColor: '#FFFFFF'
      })

    $('#altitudeSparkline')
      .sparkline([], {
        type: 'line',
        height: '45px',
        width: '90%'
      })

    $('#headingSparkline')
      .sparkline([], {
        type: 'line',
        height: '45px',
        width: '90%'
      })

    documentReady = true
  })
