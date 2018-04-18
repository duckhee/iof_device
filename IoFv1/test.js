var pump = require('./controller/pumpv1');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5;
pump.init();
console.log('end ');
process.exit();