var RaspiCam = require('raspicam'); //carmera module
var dl = require('delivery'); //send image module
var moment = require('moment'); //time module
var socket = require('socket.io-client')(''); //ip address 


var option = {
    width: 600,
    height: 420,
    mode: 'timelapse',
    awb: 'off',
    encoding: 'jpg',
    output: "./images/image_%03d.jpg", // image_000001.jpg, image_000002.jpg,... moment().format('YYYYMMDDHHmmss') + ".jpg"
    q: 50,
    timeout: 0, // take a total of 4 pictures over 12 seconds , 0 일경우 무제한 촬영
    timelapse: 1000 * 15, //1시간 단위로 촬영
    nopreview: true,
    th: '0:0:0'
};

var camera = new RaspiCam(option);

//소켓통신으로 이미지 파일을 서버로 전송
socket.on('connect', function() {
    console.log("Sockets connected");
    //delivery 패키지 이용
    delivery = dl.listen(socket);
    delivery.connect();

    delivery.on('delivery.connect', function(delivery) {

        delivery.on('send.success', function(file) {
            console.log('File sent successfully!');
        });
    });

});

// 카메라 설정 시간 간격 마다 촬영 실행
function camera_starting() {
    camera_setting(); // 처음 한번 촬영
    camera_interval = setInterval(camera_setting, 1000 * 60 * shooting_time); // 설정 시간 후에 반복 촬영
};

// 현재 시간으로 카메라 설정 세팅
function camera_setting() {
    timeInMs = moment().format('YYYYMMDDHHmmss');
    photo_path = __dirname + "/images/" + timeInMs + ".jpg";
    cmd_photo = 'raspistill -vf -t 1 -w 600 -h 420 -o ' + photo_path;
    setTimeout(() => {
        camera_shooting();
    }, 500);
};

// 설정된 값으로 카메라 촬영
function camera_shooting() {
    exec_photo(cmd_photo, function(err, stdout, stderr) {
        if (err) {
            console.log('child process exited with shooting_photo error code', err.code);
            return;
        }
        console.log("photo captured with filename: " + timeInMs);
        camera_sending();
    });
}

// 촬영 이미지 전송
function camera_sending() {
    delivery.send({
        name: timeInMs,
        path: __dirname + '/images/' + timeInMs + ".jpg",
        params: { channel: field_id, img_name: timeInMs + ".jpg" }
    });
};