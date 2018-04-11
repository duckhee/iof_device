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
        if (err) {
            setInterval(function() {
                port.get(function(err, status) {
                    if (err) {
                        console.log('get status error :::: ', err);
                    } else if (status) {
                        console.log('get port status :::: ', status);
                        port.close((err) => {
                            if (err) {
                                console.log('close error ::: ', err);
                            } else {
                                console.log('close success');
                            }
                        })
                    } else if (!status) {
                        port.open(function(err) {
                            if (err) {
                                console.log('open error ::: ', err);
                            } else {
                                port.write('i');
                            }
                        });

                    }
                });

            }, 1000);
        }

    });
}