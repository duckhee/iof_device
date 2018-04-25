var pump = require('./controller/pumpv3');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5,
    dataValue = 10,
    turnValue = 50;
pump.Toggle();
console.log('end ');