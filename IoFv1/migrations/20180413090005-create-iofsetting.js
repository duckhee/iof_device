'use strict';
module.exports = {
  up: function(queryInterface, Sequelize) {
    return queryInterface.createTable('iofsettings', {
      id: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER
      },
      st_serial: {
        type: Sequelize.STRING
      },
      st_shootingtime: {
        type: Sequelize.STRING,
        allowNull:false,
        defaultValue:'30'
      },
      st_water: {
        type: Sequelize.STRING,
        allowNull:false,
        defaultValue:'3'
      },
      st_sensingtime: {
        type: Sequelize.STRING,
        allowNull:false,
        defaultValue:'1'
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
    return queryInterface.dropTable('iofsettings');
  }
};