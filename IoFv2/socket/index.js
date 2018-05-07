'use strict';

module.exports = function(socket) {

    socket.on('connect', function() {
        console.log('socket connection success');
    });

}