var arudinoController = require('./controller/arudino');

arudinoController.sensor_info(function(err, result) {
    if (result) {
        console.log('sensor info callback :::::::::::', result);
        process.nextTick();
        arudinoController.sensor_mesurement(function(err, result) {
            if (result) {
                console.log('sensor value callback :::::::::: ', result);
            }
        });
    }
});