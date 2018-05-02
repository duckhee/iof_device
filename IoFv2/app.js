'use strict';

var express = require('express');
var path = require('path');
var db = require('./models/index');
var util = require('./util/util');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

//file send 
var dl = require('delivery');


//controller
var NeworkController = require('./dbcontroller/NetworkController');
var SettingController = require('./dbcontroller/SettingController');

//socket
const socket = require('socket.io-client')('http://13.200.19.28:5001');

//serial number
const serialNum = 'WqrWyNN8Qr3hCiXasMyZ';


//delivery connection
var delivery = dl.app.listen(socket);
console.log('delivery connection start');