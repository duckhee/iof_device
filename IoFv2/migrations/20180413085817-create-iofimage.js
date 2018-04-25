'use strict';
module.exports = {
    up: function(queryInterface, Sequelize) {
        return queryInterface.createTable('iofimages', {
            id: {
                allowNull: false,
                autoIncrement: true,
                primaryKey: true,
                type: Sequelize.INTEGER
            },
            si_serial: {
                type: Sequelize.STRING,
                allowNull: false
            },
            si_path: {
                type: Sequelize.STRING,
                allowNull: false
            },
            si_filename: {
                type: Sequelize.STRING,
                allowNull: false
            },
            si_filesize: {
                type: Sequelize.STRING,
                allowNull: false
            },
            createdAt: {
                allowNull: false,
                type: Sequelize.DATE

            },
            updatedAt: {
                allowNull: false,
                type: Sequelize.DATE

            }
        });
    },
    down: function(queryInterface, Sequelize) {
        return queryInterface.dropTable('iofimages');
    }
};