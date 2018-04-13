'use strict';

var moment = require('moment');
var arduinoController = require('../controller/arudino');
var first_chk = 0;

var sensorInfoData = '';
var flag = false;
module.exports = function(pool, socket) {
    if (flag === false) {


        arduinoController.sensor_info(function(err, result) {
            if (err) {
                console.log('arudino router info error :::::: ', err);
                console.log('arudino router info error stack :::::: ', err.stack);
                console.log('arudino router info error code :::::: ', err.code);
            } else {
                sensorInfoData = result;
                console.log('sensor info :::::: ', sensorInfoData);
                flag = true;
            }
        });
    }
    console.log('get start collect data');
    var sensorData;
    arduinoController.sensor_mesurement(function(err, result) {
        if (err) {
            console.log('arduino router mesurement error ::::: ', err);
            console.log('arduino router mesurement error ::::: ', err.stack);
            console.log('arduino router mesurement error ::::: ', err.code);
        } else {
            sensorData = result;
            console.log('get data :::: ', sensorData);
            var re = /[^\,^\-^A-Z^\d(.\d+)^\s]/gi;
            var datafilter = result.replace(re, '');
            console.log(datafilter);
            var sensorValue = datafilter.split(',');
            console.log('sensor value temp :::: ', sensorValue[2]);
            console.log('sensor value soil ::::: ', sensorValue[1]);

        }
    });
}