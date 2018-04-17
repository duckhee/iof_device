var models = require('../models/index');
var iofnetwork = require('../models/iofnetwork');

//insert network 
exports.InsertNetwork = function(network_info, callback) {
    models.iofnetwork.create({
        si_serial: network_info.serial,
        si_type: 'active'
    }).then((result) => {
        console.log('insert network result : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('insert network error : ', err);
        callback(err, null);
    });
};

//find network 
exports.FindNetwork = function(network_info, callback) {
    models.iofnetwork.findAll({
        order: [
            ['createdAt', 'DESC']
        ],
        where: {
            si_serial: network_info.serial
        }
    }).then((result) => {
        console.log('find network all result : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('find all network error : ', err);
        callback(err, null);
    });
};


//update network 
exports.UpdateNetwork = function(network_info, callback) {
    models.iofnetwork.update({
        updatedAt: models.sequelize.literal('NOW()')
    }, {
        where: {
            si_serial: network_info.serial,
            si_type: 'active'
        }
    }).then((result) => {
        console.log('update network result : ', result);
        callback(null, result);
    }).catch((err) => {
        console.log('update network error : ', err);
        callback(err, null);
    });
};