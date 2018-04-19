'use strict';
module.exports = function(sequelize, DataTypes) {
  var testing = sequelize.define('testing', {
    testing: DataTypes.STRING
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return testing;
};