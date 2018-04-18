var pump = require('./controller/pumpv1');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = 5;
pump(StatusFlag, TurnFlag).init();
console.log('end ');
process.exit();