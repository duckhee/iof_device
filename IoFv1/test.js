var arudinoController = require('./controller/arudino');

var flag = false;


arudinoController.sensor_info(function(err, result) {
    if (err) {
        console.log('info error :::::: ', err);
        process.exit();
    } else if (result) {
        console.log('sensor info :::::::::: ', result);
        arudinoController.clear_sensor(function(err, result2) {
            if (err) {
                console.log('clear data error ::::::: ', err);
                process.exit();
            } else if (result2) {
                console.log('clear data :::::::: ', result2);

                arudinoController.sensor_mesurement(function(err, result3) {
                    if (err) {
                        console.log('get data error :::::::: ', err);
                        process.exit();
                    } else if (result3) {
                        console.log('get data :::::::: ', result3);
                        arudinoController.clear_sensor(function(err, result5) {
                            if (err) {
                                console.log('clear data error ::::::: ', err);
                                process.exit();
                            } else if (result5) {
                                console.log('clear data :::::::: ', result5);
                                process.exit();
                            } else {
                                console.log('null clear data last');
                            }

                        });
                    } else {
                        console.log('null sesnor meurement ');
                    }
                });
            } else {
                console.log('null clear data first');
            }
        });
    } else {
        console.log('null sensor info ');
    }
});