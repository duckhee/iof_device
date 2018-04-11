var serialPort = require('serialport');
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
    delimiters: '\r\n'
});

var port = new serialPort('/dev/ttyACM0', {
    baudRate: 9600
});

port.pipe(parser);

port.on('open', () => {
    console.log('port open success');
});



exports.sensor_info = function(callback) {
    var datavalue = '';
    port.write('i');
    port.on('data', (data) => {
        //  console.log(data.toString());
        datavalue = data.toString();
        //return datavalue;
        callback(null, datavalue);
    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
}

exports.sensor_mesurement = function(callback) {
    var datavalue = '';
    port.write('d');
    port.on('data', (data) => {
        // console.log(data.toString());
        datavalue = data.toString();
        //return datavalue;
        callback(null, datavalue);
    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
};

exports.both_get = function(callback) {
    var datavalue = '';
    datavalue += sensor_info();
    datavalue += sensor_mesurement();
    //return datavalue;
    callback(null, datavalue);
}

exports.clear_data = function(callback) {
    var datavalue = '';
    port.write('c');
    port.on('data', (data) => {
        datavalue = data.toString();
        callback(null, datavalue);
    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
}