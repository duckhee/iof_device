'use strict';

var express = require('express');
var router = express.Router();

//db controller 
var ImageController = require('../dbcontroller/ImageController');
var SensorValueController = require('../dbcontroller/SensorValueController');
var SensorInfoController = require('../dbcontroller/SensorInfofController');
var SettingController = require('../dbcontroller/SettingController');

//user query
var models = require('../models/index');

//checking all url
router.get('/*', function(req, res, next) {
    console.log('url ::::: ', req.originalUrl);
    next();
});

//router index
router.get('/', function(req, res, next){
    SettingController.FindAllSetting(function(err, result){
        if(err){
            console.log('find all setting error :::: ', err);
            next(err);
        }else{
            console.log('setting result :::: ', JSON.stringify(result));
            res.render('index', {
                title:'Devices',
                devices:result
            });
        }
    });
});

router.get('/dashoboard/:serial', function(req, res, next){
    var getSerial = req.query.serial || req.params.serial || req.param.serial || req.body.serial;
    ImageController.LimitThreeData(getSerial, function(err, result){
        if(err){
            console.log('find image error :::::: ', err);
            next(err);
        }else{
            console.log('image data ::::: ', result);
            var ValueInfo = result;
            SensorValueController.FindImage(getSerial, function(err, result){
                if(err){
                    console.log('find sensor data limit three error ::::: ', err);
                    next(err);
                }else{
                    console.log('find limit sensor value :::: '. result);
                    try{
                        res.render('views', {
                            title:'Dashboard',
                            devices:ValueInfo,
                            img_path:result.si_path + '/' + result.si_filename
                        });
                    }catch(err){
                        console.log('try catch error :::: ', err);
                        res.render('view', {
                            title:'Dashboard',
                            devices:ValueInfo,
                            img_path:'/failed/failed.jpg'
                        });
                    }
                }
            });
        }
    });
});

router.get('/table/:serial/:page', function(req, res, next){
   var getSerial = req.params.serial || req.param.serial || req.query.serial || req.body.serial;
   var getPage = req.params.page || req.param.page || req.query.page || req.body.page;
    
});