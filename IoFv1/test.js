var arudinoController = require('./controller/arudino');

arudinoController.sensor_info(function(err, result) {
    if (err) {
        console.log('arudino get info error :::::::::: ', err);
        process.exit();
    } else {
        console.log('sensor info :::::: ', result);
    }
});

arudinoController.sensor_mesurement(function(err, result) {
    if (err) {
        console.log('arduino get mesurement error ::::::: ', err);
        process.exit();
    } else {
        console.log('get value ::::::::: ', result);
    }
});