'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofsensor = sequelize.define('iofsensor', {
    sensor_info: {
      type:DataTypes.STRING,
      allowNull:false
    }
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofsensor;
};