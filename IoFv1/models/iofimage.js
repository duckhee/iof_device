'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofimage = sequelize.define('iofimage', {
    si_serial: DataTypes.STRING,
    si_path: DataTypes.STRING,
    si_filename: DataTypes.STRING,
    si_filesize: DataTypes.STRING
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return iofimage;
};