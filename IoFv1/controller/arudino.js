var serialPort = require('serialport');
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = new serialPort('/dev/ttyACM0', {
    baudRate: 9600
});

port.pipe(parser);



exports.sensor_info = function(callback) {

    port.on('open', () => {
        console.log('port open success');
    });

    var datavalue = '';
    port.write('i');
    port.on('data', (data) => {
        //  console.log(data.toString());
        datavalue = data.toString();
        port.flush();
        //return datavalue;

    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
    port.close(function(err) {
        if (err) {
            console.log('port error :::::: ', err);
            console.log('port error :::::: ', err.stack);
        } else {
            callback(null, datavalue);
        }
    });
}

exports.sensor_mesurement = function(callback) {
    port.on('open', () => {
        console.log('port open success');
    });

    var datavalue = '';
    port.write('d');
    port.on('data', (data) => {
        // console.log(data.toString());
        datavalue = data.toString();
        //return datavalue;
        port.flush();

    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
    port.close(function(err) {
        if (err) {
            console.log('port error :::::: ', err);
            console.log('port error :::::: ', err.stack);
        } else {
            callback(null, datavalue);
        }
    });
};


exports.clear_sensor = function(callback) {
    port.on('open', () => {

    });
    var datavalue = '';
    port.write('c');
    port.on('data', (data) => {
        datavalue = data.toString();
        port.flush();

    });
    port.on('error', (err) => {
        console.log('port error :::::: ', err);
        console.log('port error :::::: ', err.stack);
        callback(err, null);
    });
    port.close(function(err) {
        if (err) {
            console.log('port error :::::: ', err);
            console.log('port error :::::: ', err.stack);
        } else {
            callback(null, datavalue);
        }
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
            this.clear_sensor(function(err, result1) {
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