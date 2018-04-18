var pump = require('./controller/pumpv2');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5;
pump(StatusFlag, TurnFlag, delayTime, dataValue, turnValue).init();
console.log('end ');