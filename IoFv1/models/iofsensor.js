'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofsensor = sequelize.define('iofsensor', {
    sensor_info: DataTypes.STRING
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofsensor;
};