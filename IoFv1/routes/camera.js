'use strict';


var moment = require('moment'); // moment 시간 모듈
var exec_photo = require('child_process').exec;
var fs = require('fs');

module.exports = function(pool, socket, delivery, serialNum, cameratime) { //함수로 만들어 객체 app을 전달받음    
    return {
        init: function() {
            console.log('get setting camera time :::: ', cameratime)
            var current_min = moment().format('m'); // 현재 시간 분 설정
            var shooting_time = cameratime; //사진 촬영 인터벌
            var sub_min = 0; //정각에서 남은 시간

            //인터벌 함수 실행
            if (current_min == 0) { // 만약 0이면 바로 촬영 시작
                sub_min = 0;
            } else { // 0이 아닐시 남은 시간 설정 후 촬영 시작
                sub_min = shooting_time - current_min;
            }

            console.log('sub_min : ' + sub_min);

            //사진한번 찍고
            this.camera_shooting();

            setTimeout(() => {
                console.log('timeout ' + sub_min + ' minute');
                setInterval(this.camera_shooting, 1000 * 60 * shooting_time); // 설정 시간 후에 반복 촬영
            }, 1000 * 60 * sub_min); // 제한된 시간 후에 촬영 시작          
        },
        // 사진 촬영 
        camera_shooting: function() {
            var timeInMs = moment().format('YYYYMMDDHHmmss');
            var dir_name = moment().format('YYYYMM');
            var photo_path = process.cwd() + "/images/" + dir_name + "/" + timeInMs + ".jpg";
            var cmd_photo = 'raspistill -vf -hf -ex auto -ev 0 -awb auto -w 1640 -h 922 -o ' + photo_path;

            //폴더 생성
            if (!fs.existsSync(process.cwd() + '/images')) {
                fs.mkdirSync(process.cwd() + '/images', '0777');
            }

            if (!fs.existsSync(process.cwd() + '/images/' + dir_name)) {
                fs.mkdirSync(process.cwd() + '/images/' + dir_name, '0777');
            }

            exec_photo(cmd_photo, function(err, stdout, stderr) {

                if (err) {
                    console.log('child process exited with shooting_photo error code', err.code);
                    console.log();
                    console.log('child process exited with shooting_photo error code :::::::::::::::: ', err);
                    console.log();
                    console.log('child process exited with shooting_photo error stack ::::::::: ', err.stack);
                    return;
                }

                console.log("photo captured with filename: " + timeInMs);
                pool.getConnection(function(err, connection) {
                    console.log("camera connetion");
                    // 마지막으로 연결된 센서 정보 가져오기
                    connection.query(' select * from iof_settings  order by createdAt desc limit 0,1 ', function(err, result, fields) {
                        if (err) {
                            if (connection) {
                                connection.release();
                            }
                            console.log('select setting error :::::::::: ', err);
                        }

                        if (result.length != 0 && result[0].st_serial) {

                            var stats = fs.statSync(process.cwd() + '/images/' + dir_name + "/" + timeInMs + ".jpg");

                            //정보 insert
                            connection.query(' insert into iof_images  (si_serial, si_path, si_filename, si_filesize, createdAt, updatedAt) values (?, ?, ?, ?, NOW(), NOW())', [result[0].st_serial, dir_name, timeInMs + ".jpg", stats.size], function(error, result2) {
                                if (error) {
                                    if (connection) {
                                        connection.release();
                                    }
                                    console.log('insert image pi error ::::::::: ', error);
                                }
                                if (!error) {
                                    console.log('insert image success ::::: ', result2);
                                    // 촬영 이미지 전송
                                    connection.release();
                                }
                            });
                            delivery.send({
                                name: timeInMs,
                                path: process.cwd() + '/images/' + dir_name + "/" + timeInMs + ".jpg",
                                params: { serial: serialNum, filename: timeInMs + ".jpg", path: dir_name, filesize: stats.size }
                            });

                        } else {
                            console.log('not setting yet');
                            connection.query('insert into iof_settings (st_serial, st_shootingtime, st_watertime) values(?,?,?)', [serialNum, 30, 5], function(err, result) {
                                if (err) {
                                    if (conn) {
                                        conn.release();
                                    }
                                    console.log('insert default setting error :::: ', err);
                                } else {
                                    console.log('default setting :::::::: ', result);
                                }
                            });
                            connection.release();
                        }


                    });
                });

            });
        }
    }
};