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
exports.both_get = function(callback) {
    var datavalue = '';
    this.sensor_info(function(err, result) {
        if (err) {
            console.log('sensor info error ::::::: ', err);
            callback(err, null);
        } else if (result) {
            console.log('sensor info :::::::::: ', result);
            datavalue += result;
            this.clear_data(function(err, result1) {
                if (err) {
                    console.log('clear arduino error ::::::: ', err);
                    callback(err, null);
                } else if (result1) {
                    console.log('clear arudino ::::: ', result1);
                    this.sensor_mesurement(function(err, result2) {
                        if (err) {
                            console.log('sensor mesurement error ::::: ', err);
                            callback(err, null);
                        } else if (result2) {
                            console.log('get mesurement :::::: ', result2);
                            datavalue += result2;
                            callback(null, datavalue);
                        } else {
                            console.log('null');
                            callback(null, null);
                        }
                    });
                } else {
                    console.log('null');
                    callback(null, null);
                }
            });

        } else {
            console.log('null');
            callback(null, null);
        }
    })

    //return datavalue;

}