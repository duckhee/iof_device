'use strict';

var util = require("../util//util");
var SettingController = require('../dbcontroller/SettingController');

module.exports = function(socket, serialNum) {
    return {
        init: function() {

        },
        getSetting: function(serialNum) {
            var serial = serialNum;
            console.log('serial number ::::: ', serialNum);
            var SendData = {
                "serial": serial,
                "msg": 1
            };
            socket.emit('checking_device', SendData);
            socket
        },
        sendSetting: function() {

        },
        updateSetting: function(updateData) {

        }
    }
}