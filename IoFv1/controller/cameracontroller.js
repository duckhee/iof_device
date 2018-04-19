'use strict';

var moment = require('moment');
var exec_photo = require('child_process').exec;
var fs = require('fs');


module.exports = function(pool, socket, delivery) {
    return {
        init: function() {
            var current_min = moment().format('m'); //set current min time
            var shooting_time = 60; //take picture time
            var sub_min = 0; // setting hour

            //interval function start
            if (current_min === 0) {
                sub_min = 0;
            } else {
                sub_min = shooting_time - current_min;
            }
            console.log('sub min ::::::::::: ', sub_min);
            //take shotting once
            this.camera_shooting();

            setTimeout(() => {
                console.log('timeout' + sub_min + ' minute');
                setInterval(this.camera_shooting, 1000 * 60 * shooting_time); //set time and while takepicture
            }, 1000 * 60 * sub_min);
        },
        camera_shooting: function() {
            var timeInMs = moment().format('YYYYMMDDHHmmss');
            var dir_name = moment().format('YYYYMM');
            var photo_path = process.cwd() + '/images/' + dir_name + '/' + timeInMs + '.jpg';
            var cmd_photo = 'raspistill -vf -hf -ex auto -ev 0 -awb auto -w 1649 -h 922 -o' + photo_path;

            //make folder
            if (!fs.existsSync(process.cwd() + '/images')) {
                fs.mkdirSync(process.cwd() + '/images', '0777');
            }
            if (!fs.existsSync(process.cwd() + '/images/' + dir_name)) {
                fs.mkdirSync(process.cwd() + '/images/' + dir_name, '0777');
            }
            exec_photo(cmd_photo, function(err, stdout, stderr) {
                if (err) {
                    console.log('child process exited with shooting photo error ::::::::::: ', err);
                    console.log();
                    console.log('child process exited with shooting photo error stack :::::::::::::::: ', err.stack);
                    console.log();
                    console.log('child process exited with shooting photo error code ::::::::::::::: ', err.code);
                    return;
                }
                console.log('photo captured with filename ::::::::::::::' + timeInMs);
                pool.getConnection(function(err, conn) {
                    if (err) {
                        if (conn) {
                            conn.release();
                        }
                        console.log('db connection error :::::: ', err);
                        console.log('db connection error :::::: ', err.stack);
                    }
                    conn.query('select * from iof_settings order by createdAt desc limit 0, 1', function(err, result, fields) {
                        if (err) {
                            if (conn) {
                                conn.release();
                            }
                            console.log('select setting query error ::::::::: ', err);
                            console.log('select setting query error ::::::::: ', err.stack);
                        }
                        console.log(result);
                        if (result.length !== 0 && result[0].st_serial) {
                            var stats = fs.statSync(process.cwd() + '/images/' + dir_name + '/' + timeInMs + '.jpg');
                            //insert info
                            conn.query('insert into iof_images () values ()', [result[0].si_serial, dir_name, timeInMs + ".jpg", stats.size], function(err, result) {
                                if (err) {
                                    if (conn) {
                                        conn.release();
                                    }
                                    console.log('insert query error ::::::::: ', err);
                                    console.log('insert query error ::::::::: ', err.stack);
                                }
                                if (!err) {
                                    console.log(result);
                                    conn.release();
                                }
                            });
                            //send capture 
                            delivery.send({
                                name: timeInMs,
                                path: process.cwd() + '/images/' + dir_name + '/' + timeInMs + '.jpg',
                                params: {
                                    serial: result[0].si_serial,
                                    filename: timeInMs + '.jpg',
                                    path: dir_name,
                                    filesize: stats.size
                                }
                            });
                        }
                        conn.release();
                    });
                });
            });
        }
    }
}