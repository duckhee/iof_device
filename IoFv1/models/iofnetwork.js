'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofnetwork = sequelize.define('iofnetwork', {
    si_serial: DataTypes.STRING,
    si_type: DataTypes.STRING
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofnetwork;
};