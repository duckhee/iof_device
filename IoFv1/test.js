<<<<<<< HEAD
var arudinoController = require('./controller/arudino');

var count = 0;

while (count === 10) {
    arudinoController.sensor_info(function(result) {

        console.log('sensor info :::::: ', result);
    });

    arudinoController.sensor_mesurement(function(result) {

        console.log('get value ::::::::: ', result);
        count++;
    });

}

if (count === 10) {
    process.exit();
}
=======
var arudinoController = require('./controller/arudino');
>>>>>>> 3649ebd52d9e28269e378af574aa9c4cc64dc6f9
