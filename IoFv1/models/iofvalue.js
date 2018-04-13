'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofvalue = sequelize.define('iofvalue', {
    sd_serial: DataTypes.STRING,
    temp: DataTypes.INTEGER,
    soil: DataTypes.INTEGER,
    textvalue: DataTypes.TEXT
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofvalue;
};