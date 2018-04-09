'use strict';

const arduinoController = require('../controller/arudino');
var moment = require('moment');
module.exports = function(pool, socket){
    
    var fisrt_chk = 0;

    var data = arduinoController.sensor_mesurement();
    console.log('get mesurement data ::::::::::: ', data);
    var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
    var datfilter = data.replace(re, '');
    console.log(dataJoin);
    var sensorObj = datfilter.split(',');
    var sensorData = [];
    var firstData = sensorObj[0];
    var secondData = sensorObj[1];
    var datajoin;
    

}