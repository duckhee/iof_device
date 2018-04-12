'use strict';
var flag = false;
var util = require('../util/util');
var testingArudino = require('../controller/arduinov1');
module.exports = function(pool, socket, serialNum) {
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
                        }
                    });
                }
            });

        } else {
            if (!util.isEmpty(data.toString()) && (data.toString().length >= 5)) {
                console.log('sensor info :::: ', data.toString());
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
                                console.log('insert sensor pu result ::::::: ', result);
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

/*

try {
    pool.getConnection(function(err, conn) {
        if (err) {
            if (conn) {
                conn.release();
            }
            console.log('insert data connection error ::::: ', err);
        } else {
            conn.query('insert iof_data into (sd_serial, temp_value, soil_value) values (?, ?, ?)', [serialNum, sensorValue[2], sensorValue[1]], function(err, result) {
                if (err) {
                    console.log('insert query error :::::: ', err);
                    conn.rollback();
                    conn.release();
                } else {
                    if (first_chk == 0) {
                        console.log('receive data !');
                        socket.on('sensor_dat_receive' + serialNum, function(data) {
                            console.log('receive data ' + serialNum + ' : ' + data);
                            if (data.msg == "1") {
                                pool.getConnection(function(err, conn) {
                                    conn.query('select * from iof_networks where sn_serial = ? and sn_type = ?', [serialNum, 'active'], function(err, result) {
                                        if (err) {
                                            if (conn) {
                                                conn.release();
                                            }
                                            console.log('select network query error :::::::::: ', err);
                                        } else {
                                            if (result.length == 0) {
                                                conn.query('insert into iof_networks (sn_serial, sn_type ) values (?, ?)', [serialNum, 'active'], function(err, result) {
                                                    if (err) {
                                                        if (conn) {
                                                            conn.release();
                                                        }
                                                        console.log('insert network query error ::::::: ', err);
                                                    } else {
                                                        console.log('insert network success ', result);
                                                    }
                                                });
                                            }
                                            if (result.length > 0) {
                                                conn.query('update iof_networks set updatedAt = NOW() where sn_serial = ? and sn_type = ?', [serialNum, 'active'], function(err, result) {
                                                    if (err) {
                                                        if (conn) {
                                                            conn.release();
                                                        }
                                                        console.log('udpate network query error :::::::: ', err);
                                                    } else {
                                                        console.log('update network success ::: ', result);
                                                    }
                                                });
                                            }
                                            conn.release();
                                        }
                                    });
                                });
                            }
                        });
                    }
                    socket.emit('sensor_data_request', sensor_obj);
                    first_chk = 1;

                }
                conn.release();
            });
        }
    });
} catch (error) {
    console.log(error);
}

*/