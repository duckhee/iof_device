'use strict';
var pigpio = require('pigpio');
var util = require('../util/util');
var gpio = pigpio.Gpio;
const switch_pump = new gpio(17, {
    mode: gpio.OUTPUT,
    //  alert: true
});
//switch_pump.setDirection('out');
module.exports = function(StatusFlag, TurnFlag, delayTime) {
    var autoFlag = true;
    var TurningFlag = false;
    var waitTime = 3;
    return {
        init: function() {
            autoFlag = StatusFlag;
            this.TurningFlag = TurnFlag;
            waitTime = delayTime;
            console.log('Hardware Revision: ' + pigpio.hardwareRevision().toString(16));
            console.log('play moter status :: ', StatusFlag);
            console.log('play moter autoFlag status :: ', autoFlag);
            console.log('Turn on off status :: ', TurnFlag);
            console.log('TurningFlag status :: ', TurningFlag);
            console.log('delay time :: ', delayTime);
            console.log('wait time :::: ', waitTime);
            //console.log('get type (input or output) : ', switch_pump.direction());
            //this.Toggle();
        },
        auto: function(delayTime) {
            console.log('start auto');
            console.log('delayTime ::: ', delayTime);
            if (!util.isEmpty(delayTime)) {
                //delay time not null
            } else {
                waitTime;
            }
        },
        Toggle: function() {
            console.log('toggle water switch : ', switch_pump.digitalRead());
            switch_pump.digitalWrite(switch_pump.digitalRead() ^ 1);
            console.log('toggle comfirm water switch : ', switch_pump.digitalRead());
        },
        manual: function(TurnStatus) {
            console.log('start not auto');
            if (TurnStatus === 0) {
                switch_pump.digitalWrite(0);
                console.log('switch pump value : ', switch_pump.digitalRead());
            } else if (TurnStatus === 1) {
                switch_pump.digitalWrite(1);
                console.log('switch pump value : ', switch_pump.direction());
            } else {
                console.log('Not value !');
            }
        },
        TimeOut: function() {
            console.log('time off');
            switch_pump.digitalWrite(0);
        }
    }

}