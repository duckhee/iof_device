'use strict';

var cameraController = require('./controller/cameracontroller');


module.exports = function(socket, serialNum) {
    socket.on('shooting_' + serialNum, function(data) {
        console.log('shooting command data :::: ', data);
        console.log('cmd ::::: ', data.cmd);
    })
}