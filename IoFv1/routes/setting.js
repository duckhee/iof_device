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
    socket.on('device_setting_check_' + serial, (data) => {
        if (data.check === 1) {
            console.log('checking this device : ', data);
            var SettingInfo = {
                "st_serial": data.serial,
                "st_shootingtime": data.st_shootingtime,
                "st_watertime": data.st_watertime
            };
            SettingController.InsertSetting(SettingInfo, function(err, result) {
                if (err) {
                    console.log('setting socket insert error :::: ', err);
                } else {
                    if (!util.isEmpty(result)) {
                        console.log('setting value : ', result);
                    } else {
                        console.log('setting null ');
                    }
                }
            });
        } else {
            console.log('not checking this device  :::: ', data);
        }
    });

}