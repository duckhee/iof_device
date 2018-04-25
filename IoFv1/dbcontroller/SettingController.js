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

//find one setting
exports.OneSetting = function(callback) {
    models.iofsetting.findOne({
        order: [
            ['createdAt', 'DESC'] //DESC는 내림 차순
        ]
    }).then((result) => {
        callback(null, result);
    }).catch((err) => {
        callback(err, null);
    });
};


//find last setting 
exports.FindSetting = function(serialNum, callback) {
    models.iofsetting.findOne({
        order: [
            ['createdAt', 'DESC']
        ]
    }).then((result) => {
        //     console.log('find device setting : ', result);
        callback(null, result);
    }).catch((err) => {
        callback(err, null);
    });
};

/*
var defaultSetting = {
            "serial": serialNum,
            "shootingtime": 30,
            "watertime": 5
        }
        this.InsertSetting(defaultSetting, function(err, result2) {
            if (err) {
                console.log('find setting and insert error :: ', err);
                callback(err, null);
            } else {
                console.log('insert default setting ::: ', result2);
                callback(null, result2);
            }
        });


*/
