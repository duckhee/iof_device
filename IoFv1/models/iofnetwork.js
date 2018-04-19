'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofnetwork = sequelize.define('iofnetwork', {
    si_serial: {
      type:DataTypes.STRING,
      allowNull:false
    },
    si_type: {
      type: DataTypes.ENUM,
      values: ['active', 'inactive'],
      defaultValue: 'inactive'
    },
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofnetwork;
};