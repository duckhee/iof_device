'use strict';

var camera = require('./routes/camera');

module.exports = function(socket, delivery, serialNum, cameraTime) {
    socket.on('shooting_' + serialNum, function(data) {
        console.log('socket testing  value :::', data);
        console.log('socket command :::: ', data.cmd);
        if (data.cmd === '1') {
            camera(socket, delivery, serialNum, cameraTime).camera_shooting();
        } else {
            console.log('not command shooting :::', data.cmd);
        }
    });
}