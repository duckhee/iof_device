var Gpio = require('pigpio').Gpio;

var Pump = new Gpio(17, {
    mode: Gpio.OUTPUT,
    alert: true
});

module.exports = function() {
    return {
        init: function() {
            this.pumpOff();

        },
        pumpOn: function() {
            this.pumpOff();
            console.log('pump on');
            Pump.digitalWrite(1);

        },
        pumpOff: function() {
            console.log('pump off');
            Pump.digitalWrite(0);
        },
        Toggle: function() {
            console.log('pump toggle');
            if (Pump.digitalRead() === 1) {
                console.log('digital value : HIGH');
                Pump.digitalWrite(0);
                this.pumpOff();
            } else if (Pump.digitalRead() === 0) {
                console.log('digital value : LOW');
                Pump.digitalWrite(1);
                this.pumpOn();
            }
            console.log('digital value : ', Pump.digitalRead());
        },
        auto: function() {
            console.log('pump auto start');
        },
        manual: function() {
            console.log('pump manual start');
            this.pumpOff();
        },
    }
}