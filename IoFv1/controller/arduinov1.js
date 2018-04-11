var SerialPort = require('serialport');

var parsers = SerialPort.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = new SerialPort('/dev/ttyACM0', {
    baudRate: 9600
});

port.pipe(parser);

port.open(function(err) {
    if (err) {
        console.log('open error :::::::: ', err);
        console.log('open error :::::::: ', err.stack);
        console.log('open error :::::::: ', err.code);
    } else {
        exports.sensor_info = function(callback) {
            port.flush();
            var datavalue = '';
            port.write('i');
            port.on('data', (data) => {
                datavalue = data.toString();
                port.flush();
            });
            port.on('error', (err) => {
                console.log('sensor info error :::::::: ', err);
                console.log('sensor info error :::::::: ', err.stack);
                console.log('sensor info error :::::::: ', err.code);
            });
            port.close(function(err) {
                if (err) {
                    console.log('sensor info close port error ::::: ', err);
                    console.log('sensor info close port error ::::: ', err.stack);
                    console.log('sensor info close port error ::::: ', err.code);
                    callback(null, err);
                } else {
                    callback(null, datavalue);
                }
            });
        }
        exports.sensor_mesurement = function(callback) {
            port.flush();
            var datavalue = '';
            port.write('d');
            port.on('data', (data) => {
                datavalue = data.toString();
                port.flush();
            });
            port.on('error', (err) => {
                console.log('sensor mesurement error :::::::: ', err);
                console.log('sensor mesurement error :::::::: ', err.stack);
                console.log('sensor mesurement error :::::::: ', err.code);
            });
            port.close(function(err) {
                if (err) {
                    console.log('sensor mesurement close port error ::::: ', err);
                    console.log('sensor mesurement close port error ::::: ', err.stack);
                    console.log('sensor mesurement close port error ::::: ', err.code);
                    callback(null, err);
                } else {
                    callback(null, datavalue);
                }
            });
        }
    }
});