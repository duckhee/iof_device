var serialPort = require('serialport');
var parsers = serialPort.parsers;
var parser = new parsers.serialPort({
    delimiters: '\r\n'
});

var port = new serialPort.parser('/dev/ttyACM0', {
    baudRate: 9600
});

port.pipe(parser);

port.on('open', () => {
    console.log('port open success');
});

port.on('error', (err) => {
    console.log('port error :::::: ', err);
    console.log('port error :::::: ', err.stack);
})

exports.sensor_info = function() {
    var datavalue = '';
    port.write('i');
    port.on('data', (data) => {
        console.log(data.toString());
        datavalue = data.toString();
        callback(null, datavalue);
    });
}

exports.sensor_mesurement = function() {
    var datavalue = '';
    port.write('d');
    port.on('data', (data) => {
        console.log(data.toString());
        datavalue = data.toString();
        callback(null, datavalue);
    });
};

exports.both_get = function() {
    var datavalue = '';
    port.write('b');
    for (var i = 0; i < 2; i++) {
        port.on('data', (data) => {
            console.log('bost data ::::: ', data.toString());
            datavalue += data.toString();
        });
    }
    callback(null, datavalue);
}