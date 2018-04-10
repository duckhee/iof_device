'use strict';

var debug = require('debug');
var path = require('path');
var dl = require('delivery');

var mysql_dbc = require('./db_con/db_con')();
console.log('testing db connection !!!');
mysql_dbc.test();
console.log(' db connection init !!!');
var pool = mysql_dbc.init();

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
            conn.query('select * from iof_image order by createdAt desc limit 0, 1', function(err, row, fileds) {
                if (err) {
                    if (conn) {
                        conn.release();
                    }
                    console.log('get image conn error :::::::: ', err);
                }
                console.log('last image info :::::::::::: ', row);
                conn.query('select * from iof_networks where si_serial = ?', [row[0].si_serial], function(err, result, fields) {
                    if (err) {
                        if (conn) {
                            conn.release();
                        }
                        console.log('select iof network error :::::::::::::: ', err);
                    }
                    if (result.length == 0) {
                        conn.query('insert into iof_networks (si_serial, si_type, createdAt) values (?,?,NOW())', [row[0].in_serial, 'active'], function(err, result) {
                            if (err) {
                                if (conn) {
                                    conn.release();
                                }
                                console.log('iof network insert error :::::::::::::: ', err);
                            }
                            if (!err) {

                            }
                        });
                    }
                    if (result.length > 0) {
                        conn.query('update iof_network set createdAt = NOW() where in_serial = ?', [row[0].in_serial], function(err, result) {
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
            });
        });
    });
});

socket.on('connect', function() {
    console.log('connection success');
})




//////////////////////////////////////////////////////////////////////////////////////////////////////////
var routes = require('./routes/index')(pool);

//var arduino = require('./routes/arduino')(pool, socket);

var camera = require('./controller/camera')(pool, socket, delivery).init();



// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

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
        error: {}
    });
});

app.set('port', process.env.PORT || 3000);

var server = app.listen(app.get('port'), function() {
    debug('Express server listening on port ' + server.address().port);
});