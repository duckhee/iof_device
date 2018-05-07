'use strict';

/*
    function sensing
    function get sensing time
    function get sensing value
    function sensing time change
*/

var serialPort = require('serialport');
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = serialPort.port('/dev/ttyACM0', {
    baudRate: 9600,
    lock: false
});

port.pipe(parser);

exports.PortOpen = function() {

}