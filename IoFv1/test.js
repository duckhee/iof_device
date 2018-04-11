var arudinoController = require('./controller/arudino');


arudinoController.sensor_mesurement(function(err, result2) {
    if (result2) {
        console.log('sensor value callback :::::::::: ', result2);
    }
});
process.nextTick(arudinoController.sensor_info(function(err, result) {
    if (result) {
        console.log('sensor info callback :::::::::::', result);


    }
}));