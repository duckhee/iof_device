'use strict';

var express = require('express');
var path = require('path');
const db = require('./models/index');
var util = require('./util/util');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var mysql = require('mysql');
//file send 
var dl = require('delivery');

//image send 
var ImageSend = require('./controller/getImage');

//db config
var config = require('./db_config/config').local;
//mysql con
var pool = mysql.createPool({
    host: 'localhost',
    user: 'candh',
    password: 'candh3869',
    database: 'iof',
});


//controller
var NeworkController = require('./dbcontroller/NetworkController');
var SettingController = require('./dbcontroller/SettingController');

//socket
const socket = require('socket.io-client')('http://13.200.19.28:5001');

//serial number
const serialNum = 'WqrWyNN8Qr3hCiXasMyZ';
const defaultCameraTime = 30;
const defaultWaterTime = 5;
const defaultSensingTime = 1;

//delivery connection
var delivery = dl.app.listen(socket);
console.log('delivery connection start');

//image get delivery
ImageSend(delivery);