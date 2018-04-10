var serialPort = require('serialport');
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
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
        return datavalue;
    });
}

exports.sensor_mesurement = function() {
    var datavalue = '';
    port.write('d');
    port.on('data', (data) => {
        console.log(data.toString());
        datavalue = data.toString();
        return datavalue;
    });
};

exports.both_get = function() {
    var datavalue = '';
    datavalue += sensor_info();
    datavalue += sensor_mesurement();
    return datavalue;
}