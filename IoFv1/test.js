var arudinoController = require('./controller/arudino');


for (var i = 0; i == 10; i++) {
    arudinoController.sensor_info(function(err, result) {
        if (result) {
            console.log('sensor info callback :::::::::::', result);
        }
    });


    arudinoController.sensor_mesurement(function(err, result) {
        if (result) {
            console.log('sensor value callback :::::::::: ', result);
        }
    })
}