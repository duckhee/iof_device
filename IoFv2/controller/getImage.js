'use strict';

var ImageController = require('../dbcontroller/ImageController');
var NetworkController = require('../dbcontroller/NetworkController');
var util = require('../util/util');
module.exports = function(delivery) {
    delivery.connect();
    delivery.on('delivery.connect', function(delivery) {
        delivery.on('send.success', function(file) {
            ImageController.FindLastImage(function(err, result) {
                if (err) {
                    console.log('find last image error ::: ', err);
                } else {
                    console.log('last image info :::::: ', result);

                    if (!util.isEmpty(result)) {
                        console.log('not empty');
                        //network checking
                        var CheckingInfo = {
                            "serial": result.si_serial
                        }
                        NetworkController.FindNetwork(CheckingInfo, function(err, result) {
                            if (err) {
                                console.log('select iof network error ::::: ', err);
                            } else {
                                if (result.length === 0) {
                                    NetworkController.InsertNetwork(CheckingInfo, function(err, result) {
                                        if (err) {
                                            console.log('iof network insert error ::::: ', err);
                                        } else {
                                            console.log('iof network insert success');
                                            console.log('network info :::: ', result);
                                        }
                                    });
                                    //network insert end
                                }
                                //result length === 0 end
                                else if (result.length > 0) {
                                    NetworkController.UpdateNetwork(CheckingInfo, function(err, result) {
                                        if (err) {
                                            console.log('update network error ::::: ', err);
                                        } else {
                                            console.log('success iof network update ');
                                        }
                                    });
                                    //update network end
                                }
                            }
                        });
                        //find network end
                    } else {
                        console.log('not image yet', result);
                    }
                }
            });
        });
    });
}