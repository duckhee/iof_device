var pump = require('./controller/pumpv3');
var Gpio = require('pigpio').Gpio;

var Pump = new Gpio(17, {
    mode: Gpio.OUTPUT,
    alert: true
});

function data() {
    console.log('pump toggle');
    if (Pump.digitalRead() === 1) {
        console.log('digital value : HIGH');
        Pump.digitalWrite(0);

    } else if (Pump.digitalRead() === 0) {
        console.log('digital value : LOW');

        Pump.digitalWrite(1);
    }
    console.log('digital value : ', Pump.digitalRead());
}
data();
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5,
    dataValue = 10,
    turnValue = 50;
pump().Toggle();
console.log('end ');