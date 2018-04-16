'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofvalue = sequelize.define('iofvalue', {
    sd_serial: DataTypes.STRING,
    temp: {
      type:DataTypes.INTEGER,
      allowNull:false,
      defaultValue:0
    },
    soil: DataTypes.INTEGER,
    textvalue: {
      type:DataTypes.TEXT,
      allowNull:false,
      defaultValue:0
    },
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofvalue;
};