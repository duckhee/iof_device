var arudinoController = require('./controller/arudino');

var flag = false;

arudinoController.both_get(function(err, result) {
    if (err) {
        console.log('bot error :::::::: ', err);
    } else if (result) {
        console.log('both value :::::: ', result);
        process.exit();
    } else {
        console.log('null');
    }
})