var mysql = require('mysql');
const config = require('../db_info/db_info').local;

module.exports = function() {
    return {
        init: function() {
            return mysql.createPool({
                cconnectionLimit: 5,
                host: config.local.host,
                port: config.local.port,
                user: config.local.user,
                password: config.local.password,
                database: config.local.databaseonfig
            });
        },

        test: function(con) {
            con.getConnection(function(err) {
                if (err) {
                    console.error('mysql connection error ::::::::::::::::: ', err);
                } else {
                    console.info('mysql connected successfully.');
                }
            });
        }
    };
};
