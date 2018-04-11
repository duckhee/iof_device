'use strict';
module.exports = function(pool, socket) {

    //수분 측정 모듈//
    var moment = require('moment'); // moment 시간 모듈
    var SerialPort = require('serialport'); //아두이노와 시리얼 통신할 수 있는 모듈
    var parsers = SerialPort.parsers;
    var fs = require('fs');
    var first_chk = 0;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    //라즈베리파이와 연결된 디바이스 주소
    var port = new SerialPort('/dev/ttyACM0', {
        baudrate: 9600
    });

    // 수분 측정
    port.pipe(parser);

    //포트 열기
    port.on('open', function() {
        console.log('port open');
        port.write('y');
    });

    // open errors will be emitted as an error event
    port.on('error', function(err) {
        console.log('Error: ', err.message);
    });

    parser.on('data', function(data) {
        port.write('y');
        /*

            string 형식
            ['측정시간','주소값 시리얼번호','측정값1','측정값2',....]

            로직 순서
            1. 데이터값 분리하여 배열 및 변수저장
            2. 디바이스 설정 테이블에 해당 디바이스 있는 지 확인
            3. 테이블에 정보가 없으면 해당 디바이스 테이블에 저장
            4. 서버에도 정보 전송
            5. 센서 정보 전송 및 테이블에 저장
            6. 전송여부 확인(테이블에 최근 전송시간 저장)
        
        */
        console.log(data);
        var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
        var datafilter = data.replace(re, '');
        console.log(dataJoin);
        var sensorObj = datafilter.split(","); // json 형식 data를 객체형식으로 저장
        var sensorData = []; // sensor data 값만 저장
        var addrSerial = sensorObj[1].split(" "); //주소값과 시리얼번호 분리
        var dataJoin; //sensor data , 구분

        if ((sensorObj.length == 26 || sensorObj.length == 14)) {

            try {

                var address = addrSerial[0]; //주소값
                var serial_num = addrSerial[1]; //시얼번호

                for (var i = 2; i < sensorObj.length; i++) {
                    sensorData[i - 2] = sensorObj[i];
                }


                //시리얼 번호 길이와 시리얼 번호가 숫자인지 확인
                if (serial_num.length == 14 && !isNaN(serial_num)) {

                    dataJoin = sensorData.join(",");

                    //받기
                    if (first_chk == 0) {
                        socket.on('device_setting_receive_' + serial_num, function(data) {
                            console.log("socket test");
                            // 디바이스 정보 확인
                            pool.getConnection(function(err, connection) {
                                //정보가 없을 시 정보 insert
                                connection.query(' update seosan_settings set st_title =  ?, st_gps = ?, st_group = ?, st_ping = 1, updatedAt = NOW() where st_serial = ? ', [data.st_title, data.st_gps, data.st_group, data.st_serial], function(error, result) {
                                    if (!error) {

                                    }
                                    connection.release();
                                });
                            });
                        });
                    }

                    // 디바이스 정보 확인
                    pool.getConnection(function(err, connection) {
                        // Use the connection
                        connection.query(' select * from seosan_settings  where st_serial = ? ', [serial_num], function(err, result, fields) {
                            if (err) console.log(err);



                            if (result.length == 0) {
                                //정보가 없을 시 정보 insert
                                connection.query(' insert into seosan_settings  (st_address, st_serial) values (?, ?)', [address, serial_num], function(error, result) {
                                    if (error) console.log(error);
                                    if (!error) {
                                        //console.log(result);
                                        var device_obj = {
                                            msg: 0,
                                            info: {
                                                st_serial: serial_num,
                                                st_address: address,
                                                st_title: '',
                                                st_gps: '',
                                                st_group: ''
                                            }
                                        };
                                        //보내기
                                        socket.emit('device_setting_request', device_obj);
                                    }

                                });
                            } else if (result[0].st_ping == 0) {
                                var device_obj = {
                                    msg: 0,
                                    info: result[0]
                                };
                                //보내기
                                socket.emit('device_setting_request', device_obj);
                            }
                            connection.release();
                        });
                    });

                    //console.log(result);
                    var sensor_obj = {
                        "sd_address": address,
                        "sd_serial": serial_num,
                        "sd_data": dataJoin,
                        "createdAt": moment().format('YYYYMMDDHHmmss')
                    };

                    //sensor data save at table of db
                    //정보가 없을 시 정보 insert
                    pool.getConnection(function(err, connection) {


                        // Use the connection
                        connection.query(' insert into seosan_data  ( sd_address, sd_serial, sd_data, createdAt ) values (?, ?, ?, ?)', [sensor_obj.sd_address, sensor_obj.sd_serial, sensor_obj.sd_data, sensor_obj.createdAt], function(error, result) {
                            if (error) console.log(error);
                            if (!error) {

                                //받기
                                if (first_chk == 0) {
                                    console.log("receive data ");
                                    socket.on('sensor_data_receive_' + serial_num, function(data) {
                                        console.log("receive data " + serial_num + ":" + data);
                                        if (data.msg == "1") {
                                            // 최근 접속 정보 저장
                                            pool.getConnection(function(err, connection) {
                                                // Use the connection
                                                connection.query(' select * from seosan_networks where sn_serial = ? and sn_type = ? ', [serial_num, 'ard'], function(err, result, fields) {
                                                    if (err) console.log(err);

                                                    if (result.length == 0) {
                                                        //정보가 없을 시 정보 insert
                                                        connection.query(' insert into seosan_networks  (sn_address, sn_serial, sn_type, createdAt) values ( ?, ?, ?, NOW() )', [address, serial_num, 'ard'], function(error, result) {
                                                            if (error) console.log(error);
                                                            if (!error) {

                                                            }

                                                        });
                                                    }

                                                    if (result.length > 0) {
                                                        //정보가 있을시 update
                                                        connection.query(' update seosan_networks  set createdAt = NOW() where sn_serial = ? and sn_type = ? ', [serial_num, 'ard'], function(error, result) {
                                                            if (error) console.log(error);
                                                            if (!error) {

                                                            }

                                                        });
                                                    }
                                                    connection.release();
                                                });
                                            });
                                        }
                                    });
                                }

                                //보내기
                                socket.emit('sensor_data_request', sensor_obj);
                                first_chk = 1;
                            }

                            connection.release();
                        });

                    });

                    // 파일 쓰기
                    try {
                        var dir_name = moment().format('YYYYMM');
                        var file_name = dir_name + ".txt";

                        //폴더 생성
                        if (!fs.existsSync(process.cwd() + '/data')) {
                            fs.mkdirSync(process.cwd() + '/data', '0777');
                        }

                        if (!fs.existsSync(process.cwd() + '/data/' + dir_name)) {
                            fs.mkdirSync(process.cwd() + '/data/' + dir_name, '0777');
                        }

                        // 루트 위치에 파일을 쓰려고 합니다.(권한 거부)
                        fs.appendFileSync(process.cwd() + '/data/' + dir_name + '/' + file_name, sensor_obj.createdAt + "," + address + "," + serial_num + "," + dataJoin + '\n', 'utf8');
                    } catch (err) {
                        console.log(err);
                    }


                    //sensor data trans to server
                    //http
                    //socket

                    var insert_url = 'http://13.124.28.87:8080/test/sensor/insert?field=' + addrSerial + '&value=' + dataJoin;
                    http.get(insert_url, (resp) => {
                        let data = '';

                        // A chunk of data has been recieved.
                        resp.on('data', (chunk) => {
                            data += chunk;
                        });

                        // The whole response has been received. Print out the result.
                        resp.on('end', () => {
                            //console.log(JSON.parse(data).explanation);
                        });

                    }).on("error", (err) => {
                        console.log("Error: " + err.message);
                    });
                }
            } catch (error) {
                console.log(error);
            }

        }
    });

}