'use strict';

var express = require('express');
var router = express.Router();

//db controller 
var ImageController = require('../dbcontroller/ImageController');
var SensorValueController = require('../dbcontroller/SensorValueController');
var SensorInfoController = require('../dbcontroller/SensorInfofController');
var SettingController = require('../dbcontroller/SettingController');

//checking all url
router.get('/*', function(req, res, next) {
    console.log('url ::::: ', req.originalUrl);
    next();
});

//router index
router.get('/', function(req, res, next){
    SettingController.
})