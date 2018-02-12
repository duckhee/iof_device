var socket = require('socket.io-client')('');//ip address 
var dl = require('delivery');//send image module
var moment = require('moment');//time module
var mqtt = require('mqtt');//mqtt server client
var clinet = mqtt.connect('mqtt://');//connection 
var http = require('http');//http module add
var serialPort = require('serialport'); //connection arduino
var parsers = serialPort.parsers;//parser serial data
var parser = new parsers.Readline({
    delimiter:'\r\n',
});
var port = new serialPort({
    baudRate:9600
});//baud rate set
var mysql_dbc = require('./db_con/db_con')();
var connection = mysql_dbc.init();
mysql_dbc.test_open(connection);

var delivery; //delivery static variable
var tempt = {}; //temp send image

