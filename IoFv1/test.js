var arudinoController = require('./controller/arudino');

var flag = false;

if (flag === false) {
    arudinoController.sensor_info();
    arudinoController.clear_data();
    flag = true;
}

while (1) {
    arudinoController.sensor_mesurement();
}