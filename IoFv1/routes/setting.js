'use strict';

var serial = 'WqrWyNN8Qr3hCiXasMyZ';

var SettingController = require('../dbcontroller/SettingController');
var util = require('../util/util');

module.exports = function(socket, serialNum) {

    if (util.isEmpty(serialNum)) {
        var sendSerial = { "serial": serial }
        socket.emit('device_setting_first', sendSerial);
    } else {
        serial = serialNum;
        var sendSerial = { "serial": serial }
        socket.emit('device_setting_first', { sendSerial });
    }


}