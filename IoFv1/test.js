var arudinoController = require('./controller/arudino');


process.nextTick(test);
process.nextTick(test1);

function test() {
    arudinoController.sensor_info(function(err, result) {
        if (result) {
            console.log('sensor info callback :::::::::::', result);

        }
    });
}

function test1() {

    arudinoController.sensor_mesurement(function(err, result2) {
        if (result2) {
            console.log('sensor value callback :::::::::: ', result2);
        }
    });

}