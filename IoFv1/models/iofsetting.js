'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofsetting = sequelize.define('iofsetting', {
    st_serial: {
      type:DataTypes.STRING,
      allowNull:false
      },
    st_shootingtime: {
      type:DataTypes.STRING,
      allowNull:false,
      defaultValue:'30'
      },
    st_water: {
      type:DataTypes.STRING,
      allowNull:false,
      defaultValue:'3'
      },
    st_sensingtime: {
      type:DataTypes.STRING,
      allowNull:false,
      defaultValue:'1'
    }
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofsetting;
};