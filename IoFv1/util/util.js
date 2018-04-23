//null checking
exports.isEmpty = function(value) {
    if (value == "" || value == null || value == undefined || (value != null && typeof value == "object" && !Object.keys(value).length)) {
        return true;
    } else {
        return false;
    }
};

//phone checking
exports.phone_number = function(phone_info) {
    var phone = new Array;
    if (phone_info) {
        if (phone_info.indexOf('-') != -1) {
            phone = phone_info.split('-');
        } else {
            phone[0] = phone_info.substr(0, 3);
            phone[1] = phone_info.substr(3, 4);
            phone[2] = phone_info.substr(7, 4);
        }

        return phone;
    } else {
        phone[0] = 000;
        phone[1] = 0000;
        phone[2] = 0000;
        return phone;
    }

}