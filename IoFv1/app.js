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
const socket = require('socket.io-client')('http://');
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
                conn.query('select * from iof_image where si_serial = ?', )
            })
        })
    })
})