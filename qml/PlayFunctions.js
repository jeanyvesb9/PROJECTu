function calcSongPlayedString(sp) {
    var hours = Math.floor(sp / 3600);
    var minutes = Math.floor((sp - (hours * 3600)) / 60);
    var seconds = sp - (hours * 3600) - (minutes * 60);

    var time = "";
    if (hours < 10) { hours = "0" + hours; }
    if (seconds < 10) { seconds = "0" + seconds; }

    if (hours !== "00") { time = hours + ':'; }
    time = time + minutes + ':' + seconds;
    return time
}

function calcSongRemString(sp, sd) {
    return '-' + calcSongPlayedString(sd - sp)
}

function calcProgressBarPerc(sp, sd) {
    return (sp / sd) * 440
}

function delay(time, cb) {
    var timer = Qt.createQmlObject("import QtQuick 2.4; Timer {}", root);
    timer.interval = time;
    timer.repeat = false;
    timer.triggered.connect(cb);
    timer.start();
}
