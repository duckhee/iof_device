var models = require('../models/index');
var iofsensor = require('../models/iofsensor');

//sensor infomation 
exports.InsertInfo = function(sensor_info, callback){
    models.iofsensor.create({
        sensor_info:sensor_info.info
    }).then((result)=>{
        console.log('insert sensor info : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('insert sensor info error : ', err);
        callback(err, null);
    });
};