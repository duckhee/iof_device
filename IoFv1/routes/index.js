'use strict';
module.exports = function(pool) { //함수로 만들어 객체 app을 전달받음
    var express = require('express');
    var router = express.Router();

    router.get('/', function(req, res) {
        pool.getConnection(function(err, connection) {
            // Use the connection
            var stmt = 'SELECT * from iof_settings';
            connection.query(stmt, function(err, rows) {
                if (err) console.error("err : " + err);
                console.log("rows : " + JSON.stringify(rows));
                connection.release();
                res.render('index', { title: 'Devices', devices: rows });
                // Don't use the connection here, it has been returned to the pool.
            });
        });
    });

    router.get('/dashboard/:serial', function(req, res) {
        pool.getConnection(function(err, connection) {
            // Use the connection
            var stmt = ' SELECT * from iof_data where sd_serial = ? order by createdAt desc limit 0,3 ';
            connection.query(stmt, [req.params.serial], function(err, rows) {
                if (err) console.error("err : " + err);
                var data_list = rows;

                var stmt = ' SELECT * from iof_images where si_serial = ? order by createdAt desc limit 0,1 ';
                connection.query(stmt, [req.params.serial], function(err, row) {
                    if (err) console.error("err : " + err);

                    connection.release();
                    res.render('view', { title: 'Dashboard', devices: data_list, img_path: row[0].si_path + "/" + row[0].si_filename });
                    // Don't use the connection here, it has been returned to the pool.
                });

            });
        });
    });

    router.get('/table/:serial/:page', function(req, res) {
        pool.getConnection(function(err, connection) {
            // Use the connection
            var stmt = ' SELECT * from iof_data where sd_serial = ? order by createdAt desc limit ?,10 ';
            connection.query(stmt, [req.params.serial, (req.params.page - 1) * 10], function(err, rows) {
                if (err) console.error("err : " + err);
                console.log("rows : " + JSON.stringify(rows));
                connection.release();
                res.render('view', { title: 'Dashboard', devices: rows });
                // Don't use the connection here, it has been returned to the pool.
            });
        });
    });

    router.post('/setting', function(req, res) {
        res.render('index', { title: 'Devices' });
    });

    return router; //라우터를 리턴
};