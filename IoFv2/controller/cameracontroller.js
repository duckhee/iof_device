'use use strict';
/*
    function init
    function shooting
    function setting 
    function delivery image
*/
var raspicam = require('raspicam');
var moment = require('moment');
var exec_photo = require('child_process').exec;
var fs = require('fs');
var ImageController = require('../dbcontroller/ImageController');
var ImageSettingController = require('../dbcontroller/SettingController');