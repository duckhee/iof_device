'use strict';

var util = require('../util/util');
var testingArudino = require('../controller/arduinov1');
module.exports = function(pool, socket, serialNum, sensingtime) {
    var moment = require('moment'); // moment 시간 모듈
    var fs = require('fs');
    var serialPort = require('serialport');
    var parsers = serialPort.parsers;
    var first_chk = 0;
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
            console.log('checking flag :::::::: ', first_chk);
            port.write('i');

        });

    } catch (e) {
        console.log('port open error try catch ::::: ', e);
    } //port 오픈 시 에러 처리 ?

    port.on('data', (data) => {
        var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
        var datafilter = data.toString().replace(re, '');
        var sensorValue = datafilter.split(',');
        /*
        //before setting server controller add
        if (first_chk == 0) {
            //보내기
            var datainfo = {
                "msg": 0
            };
            socket.emit('device_setting_request', datainfo);
            console.log('first checking ::::: ', first_chk);

            socket.on('device_setting_receive_' + serialNum, function(data) {
                console.log('get socket testing :::::: ', data);
            })
        }
        first_chk = 1;
        */
        if (!util.isEmpty(sensorValue[1])) {
            console.log('sensor value temp :::: ', sensorValue[2]);
            console.log('sensor value soil ::::: ', sensorValue[1]);

            //only soil data send 
            var sensorSoil = {
                msg: 0,
                info: {
                    "serial": serialNum,
                    "value": sensorValue[1]
                }
            }
            pool.getConnection(function(err, conn) {
                if (err) {
                    if (conn) {
                        conn.release();
                    }
                    console.log('insert data connection error ::: ', err);
                } else {
                    conn.query('insert iof_data (sd_serial, temp_value, soil_value) values (?, ?, ?)', [serialNum, sensorValue[2], sensorValue[1]], function(err, result) {
                        if (err) {
                            if (conn) {
                                conn.release();
                            }
                            console.log('insert data pi db error :::::::::::: ', err);
                        } else {
                            console.log('insert data pi result ::::: ', result);
                            socket.emit('sensor_data_request', sensorSoil);
                        }
                    });
                }
            });

        } else {
            if (!util.isEmpty(data.toString()) && (data.toString().length >= 5)) {
                pool.getConnection(function(err, conn) {
                    if (err) {
                        if (conn) {
                            conn.release();
                        }
                        console.log('insert sensor info  pi db error :::::: ', err);
                    } else {
                        conn.query('insert iof_sensor (sensor_info) values (?)', [data.toString()], function(err, result) {
                            if (err) {
                                if (conn) {
                                    conn.release();
                                }
                                console.log('insert sensor info pi db error ::::::::: ', err);
                            } else {
                                console.log('insert sensor pi result ::::::: ', result);
                            }
                        });
                    }
                });
            }
        }
        port.write('d');
    });
    port.on('error', (err) => {
        console.log('serialport error :::: ', err);


    });
}