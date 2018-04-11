var arudinoController = require('./controller/arudino');

var data_info = arudinoController.sensor_info();
var data_value = arudinoController.sensor_mesurement();

console.log('sensor info ::::::: ', data_info);
console.log('sensor value ::::::: ', data_value);