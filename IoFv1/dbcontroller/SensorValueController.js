var models = require('../models/index');
var iofvalue = require('../models/iofvalue');

//insert data
exports.InsertData = function(data_info, callback){
    models.iofvalue.create({
        sd_serial:data_info.serial,
        temp_value:data_info.tempvalue,
        soil_value:data_info.soilvalue
    }).then((result)=>{
        console.log('insert value temp, soil rocal database : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('insert value error : ', err);
        callback(err, null);
    });
};

//find data limit 3
exports.LimitThreeData = function(data_info, callback){
    models.iofvalue.findAll({
        where:{
            sd_serial:data_info.serial
        },
        order:[
            ['createdAt', 'DESC']
        ],
        limit:3
    }).then((result)=>{
        console.log('limit 3 data : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('limit 3 data error : ', err);
        callback(err, null);
    });
};

//find data limit 10
exports.LimitTenData = function(data_info, callback){
    models.iofvalue.findAll({
        order:[
            ['createdAt', 'desc']
        ],
        where:{
            st_serial:data_info.serial
        }
    }).then((result)=>{
        console.log('find ten limit data : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('find ten limit data error : ', err);
        callback(err, null);
    });
};