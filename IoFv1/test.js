var pump = require('./controller/pumpv2');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5,
    dataValue = 10,
    turnValue = 50;
pump(StatusFlag, TurnFlag, delayTime, dataValue, turnValue).init();
console.log('end ');