var onoff = require('onoff');
const gpio = onoff.Gpio;

const switch_pump = new gpio(17, 'out');

exports.control_motor = function(control_value) {
    if (control_value === 0) {
        console.log('motor turn off');
        switch_pump.writeSync(0);
    } else if (control_value === 1) {
        console.log('motor turn on');
        switch_pump.writeSync(1);
    } else {
        console.log('motor turn error');
        switch_pump.writeSync(0);
    }
}

exports.auto_motor = function(data) {
    switch (data) {
        case data:

            break;
        case data:

            break;
    }
}