var models = require('../models/index');
var iofsetting = require('../models/iofsetting');


//insert setting 
exports.InsertSetting = function(data_info, callback) {
    models.iofsetting.create({
        st_serial: data_info.serial,
        st_shootingtime: data_info.shootingtime,
        st_watertime: data_info.watertime
    }).then((result) => {
        //      console.log('insert setting : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('insert setting error : ', err);
        callback(err, null);
    });
};

//find last setting 
exports.FindSetting = function(data_info, callback) {
    models.iofsetting.find({
        order: [
            ['createdAt', 'DESC']
        ]
    }).then((result) => {
        //     console.log('find device setting : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('find device setting error : ', err);
        callback(err, null);
    });
};