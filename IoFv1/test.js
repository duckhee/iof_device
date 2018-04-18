var pump = require('./controller/pumpv1');
var StatusFlag = false,
    TurnFlag = true,
    delayTime = null;
pump(StatusFlag, TurnFlag, delayTime).init();
console.log('end ');
process.exit();