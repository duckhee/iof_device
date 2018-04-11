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
        port.on('data', (data) => {
            console.llg('i data :::: ', data.toString());
        })
    });
    var dataValue = '';

    var dataValue = '';
    port.on('data', (data) => {
        console.log('d data ? ::::: ', data.toString());
        port.write('d');
        if (!util.isEmpty(data.toString())) {
            var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
            var datafilter = data.toString().replace(re, '');
            console.log(datafilter);
            var sensorValue = datafilter.split(',');
            console.log('sensor value temp :::: ', sensorValue[2]);
            console.log('sensor value soil ::::: ', sensorValue[1]);
        }

    })


}