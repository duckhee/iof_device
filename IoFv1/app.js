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
const serialNum = '6iOAk0yqx3eRspZXuSsV'; //testing serial num

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
            conn.query('select * from iof_images order by createdAt desc limit 0, 1', function(err, row, fileds) {
                if (err) {
                    if (conn) {
                        conn.release();
                    }
                    console.log('get image conn error :::::::: ', err);
                }
                console.log('last image info :::::::::::: ', row);
                if (!util.isEmpty(row)) {
                    conn.query('select * from iof_networks where si_serial = ?', [row[0].si_serial], function(err, result, fields) {
                        if (err) {
                            if (conn) {
                                conn.release();
                            }
                            console.log('select iof network error :::::::::::::: ', err);
                        }
                        if (result.length == 0) {
                            conn.query('insert into iof_networks (si_serial, si_type, createdAt) values (?,?,NOW())', [row[0].si_serial, 'active'], function(err, result) {
                                if (err) {
                                    if (conn) {
                                        conn.release();
                                    }
                                    console.log('iof networks insert error :::::::::::::: ', err);
                                }
                                if (!err) {

                                }
                            });
                        }
                        if (result.length > 0) {
                            conn.query('update iof_networks set updatedAt = NOW() where si_serial = ?', [row[0].si_serial], function(err, result) {
                                if (err) {
                                    if (conn) {
                                        conn.release();
                                    }
                                    console.log('update network error :::::::::::::::::: ', err);
                                }
                            });
                        }
                    });
                    conn.release();
                } else {
                    console.log('not image yet ::::::::::: ', row);
                    conn.release();
                }
            });
        });
    });
});

socket.on('connect', function() {
    console.log('connection success');
})




//////////////////////////////////////////////////////////////////////////////////////////////////////////
var defaultcameratime = 30;
var defualtsensingtime = 5;
pool.getConnection(function(err, conn) {
    if (err) {
        if (conn) {
            conn.release();
        }
        console.log('get setting value error time :::::: ', err);
    } else {
        conn.query('select * from iof_settings', function(err, result) {
            if (err) {
                if (conn) {
                    conn.release();
                }
                console.log('get setting value error :::::: ', err);
            } else {
                if (!util.isEmpty(result)) {
                    console.log('get setting value :::: ', result);
                    defaultcameratime = result[0].st_shootingtime;
                    console.log('get camera time :::: ', defaultcameratime);

                } else {
                    console.log('not setting yet');
                }
            }
        })
    }
});


var routes = require('./routes/index')(pool);

var arduino = require('./routes/testarudinorouterv2.js')(pool, socket, serialNum, defualtsensingtime).init();

//var camera = require('./routes/camera')(pool, socket, delivery, serialNum, defaultcameratime).init();
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

app.set('port', process.env.PORT || 3000);

var server = app.listen(app.get('port'), function() {
    debug('Express server listening on port ' + server.address().port);
});