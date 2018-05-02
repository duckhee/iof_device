var models = require('../models/index');
var iofimage = require('../models/iofimage');

//insert image 
exports.InsertImage = function(data_info, callback) {
    models.iofimage.create({
        si_serial: data_info.serial,
        si_path: data_info.path,
        si_filename: data_info.filename,
        si_filesize: data_info.filesize
    }).then((result) => {
        //  console.log('insert images result : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('insert images error : ', err);
        callback(err, null);
    });
};

//find image last
exports.FindImage = function(serial, callback) {
    models.iofimage.findOne({
        order: [
            ['createdAt', 'DESC']
        ],
        where: {
            si_serial: serial
        }
    }).then((result) => {
        //   console.log('find one image : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('find one image error : ', err);
        callback(err, null);
    });
};

//find one
exports.FindLastImage = function(callback) {
    models.iofimage.findOne({
        order: [
            ['createdAt', 'DESC']
        ],
        limit: 1
    }).then((result) => {
        callback(null, result);
    }).catch((err) => {
        console.log('select * from iofimages order by createdAt desc limit 0, 1 error :::::', err);
        callback(err, null);
    });
}

//list 3 
exports.FindListImage = function(serial, callback) {
    models.iofimage.find({
        where: {
            si_serial: serial
        },
        order: [
            ['createdAt', 'DESC']
        ],
        limit: 3
    }).then((result) => {
        callback(null, result);
    }).catch((err) => {
        console.log('find list image error :::: ', err);
        callback(err, null);
    });
}