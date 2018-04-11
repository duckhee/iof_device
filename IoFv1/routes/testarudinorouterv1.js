'use strict';
var flag = false;
var util = require('../util/util');
module.exports = function(pool, socket) {
    var moment = require('moment'); // moment 시간 모듈
    var fs = require('fs');
    var serialPort = require('serialport');
    var parsers = serialPort.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    var port = new serialPort('/dev/ttyACM0', {
        baudRate: 9600
    });

    port.pipe(parser);


    port.on('open', () => {
        console.log('port open success');
        port.write('i');

    });
    var dataValue = '';

    var dataValue = '';
    port.on('data', (data) => {
        console.log('data ::::: ', data.toString());
        port.write('d');

        var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
        var datafilter = data.toString().replace(re, '');
        var sensorValue = datafilter.split(',');
        if (!util.isEmpty(sensorValue[1])) {
            console.log(datafilter);
            console.log('sensor value temp :::: ', sensorValue[2]);
            console.log('sensor value soil ::::: ', sensorValue[1]);
        }

    })


}