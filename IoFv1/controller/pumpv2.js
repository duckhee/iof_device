'use strict';

var onoff = require('onoff');
var util = require('../util/util');
var GPIO = onoff.Gpio;
var pump_switch = new GPIO(17, 'out');


module.exports = function(StatusFlag, TurnFlag, delayTime) {
    var autoFlag = true;
    var TurningFlag = false;
    var waitTime = 3;
    return {
        init: function() {
            autoFlag = StatusFlag;
            TurningFlag = TurnFlag;
            waitTime = delayTime;
            console.log('auto flag : ', autoFlag);
            console.log('insert auto flag : ', StatusFlag);
            console.log('manual turn flag : ', TurningFlag);
            console.log('manual turn flag insert : ', TurnFlag);
            console.log('waiting time : ', waitTime);
            console.log('waiting time insert : ', delayTime);
            if (autoFlag) {
                console.log('auto set');
                this.auto(waitTime);
            } else {
                console.log('manual set');
                this.manual(this.TruningFlag);
            }

        },
        manual: function(TruningFlag) {
            console.log('tesitng manual function');
            if (TurningFlag === true) {
                console.log('gpio pin status : ', pump_switch.readSync());
                pump_switch.writeSync(1);
                console.log('gpio pin status : ', pump_switch.readSync());
                this.Toggle(3);
                console.log('gpio pin status : ', pump_switch.readSync());
            } else {
                console.log('gpio pin status : ', pump_switch.readSync());
                pump_switch.writeSync(0);
                console.log('gpio pin status : ', pump_switch.readSync());

            }
        },
        auto: function(waitTime) {

        },
        Toggle: function(waitting) {
            setTimeout(() => {
                console.log('gpio pin status : ', pump_switch.readSync());
                pump_switch.writeSync(pump_switch.readSync() ^ 1);
            }, 1000 * waitting); //1000*60*3 default
        }
    }
}