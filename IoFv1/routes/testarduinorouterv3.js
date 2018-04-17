'use strict';

var moment = require('moment'); // moment 시간 모듈
var fs = require('fs');
var serialPort = require('serialport');
var util = require('../util/util');

var ImageController = require('../dbcontroller/ImageController');
var NetworkController = require('../dbcontroller/NetworkController');
var SensorInfoController = require('../dbcontroller/SensorInfofController');
var SensorValueController = require('../dbcontroller/SensorValueController');
var SettingController = require('../dbcontroller/SettingController');

var flag = false;

module.exports = function(socket, serialNum, defualtsensingtime) {
    return {
        init: function() {
            console.log('get setting sensing time :::: ', defualtsensingtime)
            var current_min = moment().format('m'); // 현재 시간 분 설정
            var defualtsensingtime = defualtsensingtime; //사진 촬영 인터벌
            var sub_min = 0; //정각에서 남은 시간

            //인터벌 함수 실행
            if (current_min == 0) { // 만약 0이면 바로 촬영 시작
                sub_min = 0;
            } else { // 0이 아닐시 남은 시간 설정 후 촬영 시작
                sub_min = defualtsensingtime - (defualtsensingtime + current_min % defualtsensingtime);
            }
            console.log('sensing sub_min : ' + sub_min);


            //처음 센싱 시작
            this.sensing();

            // setTimeout(() => {
            //     console.log('timeout ' + sub_min + ' minute');
            //     setInterval(this.sensing, 1000 * 60 * defualtsensingtime); // 설정 시간 후에 반복 촬영
            // }, 1000 * 60 * sub_min); // 제한된 시간 후에 촬영 시작       

        },
        sensing: function() {
            console.log('sensing start');
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
                console.log('sensor value : ', sensorValue);
                if (sensorValue === '\r\n') {
                    console.log('null data insert');
                    port.write('i');
                }
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
                    var sensordataInfo = {
                        serial: serialNum,
                        tempvalue: sensorValue[2],
                        soilvalue: sensorValue[1]
                    }
                    console.log('sensor value temp :::: ', sensorValue[2]);
                    console.log('sensor value soil ::::: ', sensorValue[1]);

                    SensorValueController.InsertData(sensordataInfo, function(err, result) {
                        if (err) {
                            console.log('insert data error : ', err);
                        } else {
                            //   console.log('insert data pi result ::::: ', result);
                            socket.emit('sensor_data_request', sensorSoil);
                            port.flush();
                            port.write('d');
                        }
                    });
                } else {
                    if (!util.isEmpty(data.toString()) && (data.toString().length >= 5) && flag === false) {
                        console.log('get sensor info ');
                        var SensorInfo = {
                            info: data.toString()
                        };
                        SensorInfoController.InsertInfo(SensorInfo, function(err, result) {
                            if (err) {
                                console.log('sensor infomation error : ', err);
                            } else {
                                //  console.log('insert sensor pi result ::::::: ', result);
                                flag = true;
                                port.write('d');
                            }
                        });
                    }
                }
            });
            port.on('error', (err) => {
                console.log('serialport error :::: ', err);
            });
        }
    }
}