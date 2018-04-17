var fs = require('fs');
var moment = require('moment');


exports.ReadWrite = function(write_info, callback) {
    var data_format = moment().formant('YYYYMMDD');
    //make folder and check
    if (!fs.existsSync(process.cwd() + '/data/' + data_format)) {
        fs.mkdirSync(process.cwd() + '/data/' + data_format, '0777');
    }
    //write data
    fs.writeFileSync()
};