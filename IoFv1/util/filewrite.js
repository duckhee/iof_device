var fs = require('fs');
var moment = require('moment');

//write db data
exports.ReadWrite = function(write_info, callback) {
    var dir_name = moment().formant('YYYYMMDD');
    var file_name = dir_name + '.txt';
    try {
        //make data folder
        if (!fs.existsSync(process.cwd() + '/data')) {
            fs.mkdirSync(process.cwd() + '/data', '0777');
        }
        //make folder and check
        if (!fs.existsSync(process.cwd() + '/data/' + dir_name)) {
            fs.mkdirSync(process.cwd() + '/data/' + dir_name, '0777');
        }
        //write data(permission reject)
        fs.appendFileSync(process.cwd() + '/data/' + dir_name + '/' + file_name, write_info.createdAt + ',' + write_info.address + ',' + write_info.data + '\r\n', 'utf8');
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