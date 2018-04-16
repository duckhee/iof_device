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
        allowNull:false
      },
      si_path: {
        type: Sequelize.STRING,
        allowNull:false
      },
      si_filename: {
        type: Sequelize.STRING,
        allowNull:false
      },
      si_filesize: {
        type: Sequelize.STRING,
        allowNull:false
      },
      createdAt: {
        allowNull: false,
        type: 'TIMESTAMP',
        defaultValue: Sequelize.literal('CURRENT_TIMESTAMP'),
      },
      updatedAt: {
        allowNull: false,
        type: 'TIMESTAMP',
        defaultValue: Sequelize.literal('CURRENT_TIMESTAMP'),
      }
    });
  },
  down: function(queryInterface, Sequelize) {
    return queryInterface.dropTable('iofimages');
  }
};