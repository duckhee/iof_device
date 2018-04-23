var serialPort =require('serialport');
var http = require('http');
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

var port = new serialPort({
    baudRate:9600,
});

module.exports = function()
{
    port.pipe(parser);
    //port open method
    port.on('open', function(){
        console.log('port open');
    });
    //port error method
    port.on('error', function(err){
        console.log('error : ', err);
    });
    //port get data
    port.on('data', function(data){
        console.log('data info : ', data);
    });


    return port;
}