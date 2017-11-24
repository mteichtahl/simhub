const API_URL = '<INSERT_API_GATEWAY_URL_HERE>'

const MAX_HISTORY = 60
const FREQ = 1

var interval = 1000 / FREQ
var map
var marker

var dataHistory =
    {
      airspeed: new CBuffer(MAX_HISTORY),
      altitude: new CBuffer(MAX_HISTORY),
      heading: new CBuffer(MAX_HISTORY),
      pitch: new CBuffer(MAX_HISTORY),
      roll: new CBuffer(MAX_HISTORY),
      yaw: new CBuffer(MAX_HISTORY),
      lat: new CBuffer(MAX_HISTORY),
      lng: new CBuffer(MAX_HISTORY),
      vspeed: new CBuffer(MAX_HISTORY),
      timestamp: undefined
    }

    function getData(cb) {
      $.ajax({
        url: API_URL,
        contentType: 'application/json; charset=utf-8',
        dataType: 'json',
        cors: true,
        success: function(data) {
          var heading = parseFloat(data.Item.heading.S).toFixed(2);
          var airspeed = parseFloat(data.Item.airspeed.S).toFixed(2);
          var pitch = parseFloat(data.Item.pitch.S).toFixed(2);
          var roll = parseFloat(data.Item.roll.S).toFixed(2);
          var yaw = parseFloat(data.Item.yaw.S).toFixed(2);
          var altitude = parseFloat(data.Item.altitude.S).toFixed(0);
          var lat = parseFloat(data.Item.lat.S);
          var lng = parseFloat(data.Item.lng.S);
          var vs = parseFloat(data.Item.vspeed.S).toFixed(2)

          dataHistory.airspeed.push(airspeed)
          dataHistory.altitude.push(altitude)
          dataHistory.heading.push(heading)
          dataHistory.lat.push(lat)
          dataHistory.lng.push(lng)
          dataHistory.pitch.push(pitch)
          dataHistory.roll.push(roll)
          dataHistory.yaw.push(yaw)
          dataHistory.vspeed.push(vs)
          dataHistory.timestamp = data.Item.sts.S

          cb(data.Item)
        }
      })
    }

    $(document)
        .ready(function() {
          $.support.cors = true
          var map = undefined

          var attitude = $.flightIndicator(
              '#attitude', 'attitude',
              {roll: 50, pitch: -20, size: 200, showBox: false});
          var heading = $.flightIndicator(
              '#heading', 'heading', {heading: 0, showBox: false});
          var variometer = $.flightIndicator(
              '#variometer', 'variometer', {vario: 0, showBox: true});
          var airspeed = $.flightIndicator(
              '#airspeed', 'airspeed', {airspeed: 0, showBox: false});
          var altimeter = $.flightIndicator(
              '#altimeter', 'altimeter', {altitude: 0, showBox: false});

          map = new GMaps(
              {el: '#locationMap', lat: -12.043333, lng: -77.028333, zoom: 11})

          if (map)
            google.maps.event.addListenerOnce(
              map.map, 'tilesloaded',
              function () {
              
              })

          $('#airspeedSparkline').sparkline([], {
            type: 'line',
            width: '90%',
            height: '45px',
            fillColor: '#FFFFFF'
          })
          $('#altitudeSparkline')
              .sparkline([], {type: 'line', height: '45px', width: '90%'})
          $('#headingSparkline')
              .sparkline([], {type: 'line', height: '45px', width: '90%'})
       
          setInterval(function() {
            getData(function(data) {
              map.setCenter(
                  dataHistory.lat.last(), dataHistory.lng.last(), function() {
                    marker = map.createMarker({
                      lat: dataHistory.lat.last(),
                      lng: dataHistory.lng.last(),
                      title: 'test'
                    })
                    map.addMarker(marker)
                  })

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

        
              $('#headingText').text(dataHistory.heading.last())
              $('#airspeedText').text(dataHistory.airspeed.last())
              $('#altitudeText').text(dataHistory.altitude.last())
              $('#atitudeText').text(
                  `${dataHistory.pitch.last()}/${dataHistory.roll.last()}`
                  )
              $('#timeStamp')
                  .text(moment(dataHistory.timestamp)
                            .format('hh:mm:ss.m ddd DD/MM/YYYY'))

              attitude.setPitch(dataHistory.pitch.last())
              attitude.setRoll(dataHistory.roll.last())
              heading.setHeading(dataHistory.heading.last())
              airspeed.setAirSpeed(dataHistory.airspeed.last())
              altimeter.setAltitude(dataHistory.altitude.last())
            })
          }, interval)
        })
