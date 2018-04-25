'use strict';
module.exports = function(sequelize, DataTypes) {
  var iofimage = sequelize.define('iofimage', {
    si_serial: {
      type:DataTypes.STRING,
      allowNull:false
    },
    si_path: {
      type:DataTypes.STRING,
      allowNull:false
    },
    si_filename: {
      type:DataTypes.STRING,
      allowNull:false
    },
    si_filesize: {
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
  return iofimage;
};