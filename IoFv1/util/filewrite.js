var fs = require('fs');
var moment = require('moment');

//write db data
exports.ReadWrite = function(write_info, callback) {
    var data_format = moment().formant('YYYYMMDD');
    //make folder and check
    if (!fs.existsSync(process.cwd() + '/data/' + data_format)) {
        fs.mkdirSync(process.cwd() + '/data/' + data_format, '0777');
    }
    //write data
    try {
        fs.writeFileSync(data_format + '.txt', write_info, 'utf8');
        console.log('write file success ');
        callback(null);
    } catch (err) {
        console.log('write file error ::: ', err);
        callback(err);
    }
};

//log error 
exports.ErrorLog = function(error_info, callback) {

}