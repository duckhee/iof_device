
//controller
var pump = require('../controller/pumpv2');
var camera = require('./camera');

StatusFlag, TurnFlag, delayTime, dataValue, turnValue

//controller device
module.exports = function(io, socket, serialNum,delivery, cameratime, StatusFlag, TurnFlag, delayTime, dataValue, turnValue){
    
    //pump start socket event
    socket.on('pumpstart_'+serialNum, function(data){
        console.log('pump start data ::::: ', data);
        pump(StatusFlag, TurnFlag, delayTime, dataValue, turnValue).start();
    });


    //pump stop socket event
    socket.on('pumpstop_'+serialNum, function(data){
        console.log('pump stop data :::: ', data);
        pump(StatusFlag, TurnFlag, delayTime, dataValue, turnValue).stop();
    });

    //camera shooting socket event
    socket.on('shooting_'+serialNum, function(data){
        console.log('shooting camera data ::: ', data);
        camera(socket, serialNum, delivery, cameratime).camera_shooting();
        var shootingCheck = {
            "serial":serialNum,
            "flag":1
        };
        io.emit('shooting_success', shootingCheck);
    });
}