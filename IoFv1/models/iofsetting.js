'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofsetting = sequelize.define('iofsetting', {
    st_serial: DataTypes.STRING,
    st_shootingtime: DataTypes.STRING,
    st_water: DataTypes.STRING,
    st_sensingtime: DataTypes.STRING
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofsetting;
};