'use strict';
var flag = false;
var util = require('../util/util');
var testingArudino = require('../controller/arduinov1');
module.exports = function(pool, socket) {
    var moment = require('moment'); // moment 시간 모듈
    var fs = require('fs');
    var serialPort = require('serialport');
    var parsers = serialPort.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    var port = new serialPort('/dev/ttyACM0', {
        baudRate: 9600,
        lock: false
    });

    port.pipe(parser);

    try {
        //포트 열기
        port.on('open', function() {
            port.flush();
            console.log('port open');
            port.write('i');

        });

    } catch (e) {
        console.log('port open error try catch ::::: ', e);
    } //port 오픈 시 에러 처리 ?

    port.on('data', (data) => {
        var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
        var datafilter = data.toString().replace(re, '');
        var sensorValue = datafilter.split(',');
        if (!util.isEmpty(sensorValue[1])) {
            console.log('sensor value temp :::: ', sensorValue[2]);
            console.log('sensor value soil ::::: ', sensorValue[1]);

        } else {
            if (!util.isEmpty(data.toString()) && (data.toString().length >= 5)) {
                console.log('sensor info :::: ', data.toString());
            }
        }
        port.write('d');
    });
    port.on('error', (err) => {
        console.log('serialport error :::: ', err);


    });
}