//default config
var config = require('./config.json');

//var field_id = config.channel; // field_id 값 설정
//var water_stop_time = config.water_stop_time; // water_stop_time 값 설정
//var shooting_time = config.shooting_time; //shooting time 값 설정

var current_min; //current min
var sub_min; //before start capture
var camera_interval; //camera setting value

// user camera capture set
var timeInMs;
var exex_photo = require('child_process').exec; //thread two child process use
var photo_path;
var cmd_photo;

var socket = require('socket.io-client')('http://'); //setting and camera socekt module set
var dl = require('delivery'); //send file module
var moment = require('moment'); //time set module
var mqtt = require('mqtt'); //mqtt server module
var client = mqtt.connect('mqtt://'); //mqtt server connected
var http = require('http'); //http server module
var delivery; //set parameter delivery

var temp = {}; //socket setting image path object

//controller setting
var GPIO = require('onoff').Gpio;
var onoffcontroller = new GPIO(21,'out');

//get serial get arduino sensor value
var SerialPort = require('serialport');
var parsers = SerialPort.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

var port = new SerialPort('/dev/ttyACM0', {
    
})

