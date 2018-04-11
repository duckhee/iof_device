//var arudinoController = require('./controller/arudino');
var arudinoController = require('./controller/arduinov1');

var flag = false;


arudinoController.sensor_info(function(err, result) {
    if (err) {
        console.log('info error :::::: ', err);
        process.exit();
    } else if (result) {
        console.log('sensor info :::::::::: ', result);
        arudinoController.sensor_mesurement(function(err, result3) {
            if (err) {
                console.log('get data error :::::::: ', err);
                process.exit();
            } else if (result3) {
                console.log('get data :::::::: ', result3);
                process.exit();

            } else {
                console.log('null sesnor meurement ');
            }
        });

    } else {
        console.log('null sensor info ');
    }
});