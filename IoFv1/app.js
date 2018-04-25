'use strict';

var debug = require('debug');
var path = require('path');
var dl = require('delivery');
var mysql = require('mysql');
var db_config = require('./db_info/db_info').local;
var util = require('./util/util');

var express = require('express');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var mysql_dbc = require('./db_con/db_con')();
console.log('testing db connection !!!');
//mysql_dbc.test();
console.log(' db connection init !!!');
//var pool = mysql_dbc.init();
var pool = mysql.createPool({
    host: 'localhost',
    user: 'candh',
    password: 'candh3869',
    database: 'iof',
});
const serialNum = 'WqrWyNN8Qr3hCiXasMyZ'; //testing serial num
var NeworkController = require('./dbcontroller/NetworkController');
var SettingController = require('./dbcontroller/SettingController');
//get socket io
const socket = require('socket.io-client')('http://13.209.19.28:5001');
//delivery package 
var delivery = dl.listen(socket);
console.log('delivery conneciton start');
delivery.connect();
//delivery get connection log
delivery.on('delivery.connect', function(delivery) {
    delivery.on('send.success', function(file) {
        pool.getConnection(function(err, conn) {
            //use the connection
            //get last save image info 
            conn.query('select * from iofimages order by createdAt desc limit 0, 1', function(err, row, fileds) {
                if (err) {
                    if (conn) {
                        conn.release();
                    }
                    console.log('get image conn error :::::::: ', err);
                }
                console.log('last image info :::::::::::: ', row[0].si_serial);

                if (!util.isEmpty(row)) {
                    console.log('not empty ');
                    //network checking 
                    var checkingInfo = {
                        serial: row[0].si_serial
                    };
                    NeworkController.FindNetwork(checkingInfo, function(err, result) {
                        if (err) {
                            console.log('select iof network error :::::::::::::: ', err);
                        } else {
                            if (result.length == 0) {
                                var network_info = {
                                    serial: row[0].si_serial
                                }
                                NeworkController.InsertNetwork(network_info, function(err, result) {
                                    if (err) {
                                        console.log('iof networks insert error :::::::::::::: ', err);
                                    } else {
                                        console.log('success iof neworks insert ');
                                    }
                                });
                            }
                            if (result.length > 0) {
                                var networkInfo = {
                                    serial: row[0].si_serial
                                }
                                NeworkController.UpdateNetwork(networkInfo, function(err, result) {
                                    if (err) {
                                        console.log('update network error :::::::::::::::::: ', err);
                                    } else {
                                        console.log('success iofnetwork update ');
                                    }
                                });
                            }
                        }
                    });
                } else {
                    console.log('not image yet ::::::::::: ', row);
                }
            });
        });
    });
});

socket.on('connect', function() {
    console.log('socket connection success');
});







//////////////////////////////////////////////////////////////////////////////////////////////////////////
var defaultcameratime = 30;
var defualtsensingtime = 5;
var SettingData = {
    "serial": serialNum,
    "shootingtime": defaultcameratime,
    "watertime": defualtsensingtime
}

SettingController.FindSetting(function(err, result) {
    if (err) {
        console.log('findsetting first error : ', err);
        SettingController.InsertSetting(SettingData, function(err, result) {
            if (err) {
                console.log('insert setting default error : ', err);
            }
        });
    }
});
//first setting checking here


var routes = require('./routes/index')(pool);

var arduino = require('./routes/testarduinorouterv3.js')(socket, serialNum, 5).init();

var camera = require('./routes/camera')(socket, delivery, serialNum, 30).init();
/*
process.on('unhandledRejection', error => {
    throw error
}); //경고 시 종료 처리 ? 
*/
var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use('/public', express.static(path.join(__dirname, 'public')));
app.use('/images', express.static(path.join(__dirname, 'images')));

app.use('/', routes);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: err
    });
});

app.set('port', process.env.PORT || 9090);

var server = app.listen(app.get('port'), function() {
    debug('Express server listening on port ' + server.address().port);
});