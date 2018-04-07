var onoff = require('onoff');
const gpio = onoff.Gpio;

const switch_pump = new gpio(17, 'out');

exports.control_motor = function(control_value) {
    if (control_value === 0) {
        console.log('motor turn off');
    } else if (control_value === 1) {
        console.log('motor turn on');
    } else {
        console.log('motor turn error');
    }
}