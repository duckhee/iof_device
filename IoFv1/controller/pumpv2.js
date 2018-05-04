'use strict';

var onoff = require('onoff');
var util = require('../util/util');
var GPIO = onoff.Gpio;
var pump_switch = new GPIO(4, 'out');


module.exports = function(StatusFlag, TurnFlag, delayTime, dataValue, turnValue) {
    var autoFlag = true;
    var TurningFlag = false;
    var waitTime = 3;
    return {
        init: function() {
            autoFlag = StatusFlag;
            TurningFlag = TurnFlag;
            waitTime = delayTime;
            console.log('data type : ', typeof(dataValue));
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
                console.log('gpio pin status before write : ', pump_switch.readSync());
                pump_switch.writeSync(1);
                console.log('gpio pin status after write : ', pump_switch.readSync());
                this.Toggle(3);
                console.log('gpio pin status : ', pump_switch.readSync());
            } else {
                console.log('gpio pin status : ', pump_switch.readSync());
                pump_switch.writeSync(0);
                console.log('gpio pin status : ', pump_switch.readSync());

            }
        },
        auto: function(waitTime, dataValue, turnValue) {
            if (!util.isEmpty(dataValue)) {
                console.log('data value null set start last default time and stop ');
            } else {
                console.log('start dataValue limit');
            }

        },
        Toggle: function(waitting) {
            console.log('waitting time toggle : ', waitTime);
            setTimeout(() => {
                console.log('gpio pin status before toggle : ', pump_switch.readSync());
                pump_switch.writeSync(pump_switch.readSync() ^ 1);
                console.log('gpio pin status after toggle : ', pump_switch.readSync());
            }, 1000 * 60 * waitting); //1000*60*3 default
        },
        start:function(){
            console.log('pump start function');
            pump_switch.writeSync(1);
            setTimeout(()=>{
                console.log('pump stop few min ...... ');
                pump_switch.writeSync(pump_switch.readSync()^1);
                
            }, 1000*30);
        },
        stop:function(){
            console.log('pump stop function');
            pump_switch.writeSync(0);
        },

    }
}