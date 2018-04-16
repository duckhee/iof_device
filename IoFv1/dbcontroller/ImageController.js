var models = require('../models/index');
var iofimage = require('../models/iofimage');

//insert image 
exports.InsertImage = function(data_info, callback){
    models.iofimage.create({
        si_serial:data_info.serial,
        si_path:data_info.path,
        si_filesize:data_info.filesize
    }).then((result)=>{
        console.log('insert images result : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('insert images error : ', err);
        callback(err, null);
    });
};

//find image last
exports.FindImage = function(data_info, callback){
    models.iofimage.findOne({
        order:[
            ['createdAt', 'DESC']
    ]
    }).then((result)=>{
        console.log('find one image : ', result);
        callback(null, result);
    }).catch((err)=>{
        console.log('find one image error : ', err);
        callback(err, null);
    });
};