var arudinoController = require('./controller/arudino');

arudinoController.sensor_info(function(result) {


    console.log('sensor info :::::: ', result);
});

arudinoController.sensor_mesurement(function(result) {

    console.log('get value ::::::::: ', result);

});