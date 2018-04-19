'use strict';
module.exports = {
  up: function(queryInterface, Sequelize) {
    return queryInterface.createTable('iofvalues', {
      id: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER
      },
      sd_serial: {
        type: Sequelize.STRING,
        allowNull:false,
        defaultValue:0
      },
      temp: {
        type: Sequelize.INTEGER,
        allowNull:false,
        defaultValue:0    
      },
      soil: {
        type: Sequelize.INTEGER,
        allowNull:false,
        defaultValue:0
      },
      textvalue: {
        type: Sequelize.TEXT,
        allowNull:false,
        defaultValue:'0'
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
    return queryInterface.dropTable('iofvalues');
  }
};