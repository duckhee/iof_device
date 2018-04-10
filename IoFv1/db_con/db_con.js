var mysql = require('mysql');
const config = require('../db_info').local;

module.exports = function() {
    return {
        init: function() {
            return mysql.createPool({
                cconnectionLimit: 5,
                host: config.host,
                port: config.port,
                user: config.user,
                password: config.password,
                database: config.databaseonfig
            });
        },

        test: function(con) {
            con.connect(function(err) {
                if (err) {
                    console.error('mysql connection error ::::::::::::::::: ', err);
                } else {
                    console.info('mysql connected successfully.');
                }
            });
        }
    };
};