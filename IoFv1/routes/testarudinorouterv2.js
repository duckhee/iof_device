'use strict';

var moment = require('moment'); // moment 시간 모듈
var fs = require('fs');
var serialPort = require('serialport');
var util = require('../util/util');
var testingArudino = require('../controller/arduinov1');

var flag = false;

module.exports = function(pool, socket, serialNum, defualtsensingtime) {
    return {
        init: function() {
            console.log('get setting sensing time :::: ', defualtsensingtime)
            var current_min = moment().format('m'); // 현재 시간 분 설정
            var timesensor = defualtsensingtime; //센서 촬영 인터벌
            var sub_min = 0; //정각에서 남은 시간

            //인터벌 함수 실행
            if (current_min == 0) { // 만약 0이면 바로 센서 작동
                sub_min = 0;
            } else { // 0이 아닐시 남은 시간 설정 후 센서 작동
                sub_min = timesensor - current_min / 5;
            }

            console.log('sub_min : ' + sub_min);

            //사진한번 찍고
            this.sensing();

            setTimeout(() => {
                console.log('timeout ' + sub_min + ' minute');
                setInterval(this.sensing, 1000 * 60 * 1); // 설정 시간 후에 센서 작동
            }, 1000 * 60 * 1); // 제한된 시간 후에 센서 작동        
        },
        sensing: function() {
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

                    setTimeout(() => {
                        console.log('timeout ' + sub_min + ' minute');
                        setInterval(function() {
                            console.log('interval ');
                            port.write('d');
                        }, 1000 * 60 * timesensor); // 설정 시간 후에 반복 촬영
                    }, 1000 * 60 * sub_min); // 제한된 시간 후에 촬영 시작         
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
                                    //   port.write('d');
                                }
                            });
                        }
                    });

                } else {
                    if (!util.isEmpty(data.toString()) && (data.toString().length >= 5) && flag === false) {
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
                        flag = true;

                        port.write('d');
                    }
                }
            });
            port.on('error', (err) => {
                console.log('serialport error :::: ', err);
            });
        }
    }
}