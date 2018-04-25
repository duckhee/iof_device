'use strict';
module.exports = {
    up: function(queryInterface, Sequelize) {
        return queryInterface.createTable('iofnetworks', {
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
            si_type: {
                type: Sequelize.ENUM('active', 'inactive'),
                defaultValue: 'inactive'
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
        return queryInterface.dropTable('iofnetworks');
    }
};