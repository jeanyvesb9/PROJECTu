import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias image: backgroundImage.source
    property bool playing
    property var _options: ["Albums", "Artists", "Songs", "Playlists", "Genres", "Spotify", "Airplay", "Settings"]
    signal show()

    signal play()
    Keys.onTabPressed: { play() }

    Component.onCompleted: {
        for (var i in _options) {
            listModel.append({"name": _options [i]});
        }
    }

    onPlayingChanged: {
        if (playing) {
            listModel.insert(0, {"name": "Now Playing"});
        }
        else {
            listModel.remove(0, 1);
        }
    }

    onFocusChanged: {
        if(focus) {
            optionsUI.highlightMoveDuration = 0;
            optionsUI.currentIndex = 0;
            optionsUI.highlightMoveDuration = -1;
        }
    }

    Keys.onLeftPressed: optionsUI.decrementCurrentIndex()
    Keys.onRightPressed: optionsUI.incrementCurrentIndex()

    Keys.onReturnPressed: {
        var n = optionsUI.currentIndex;
        if (playing) {
            if (n == 0) {
                nowPlaying.state = "normal";
                nowPlaying.from = "home";
                nowPlaying.focus = true;
                window.
                return;
            }
            else {
                n -= 1;
            }
        }
        switch (n) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            songPage.from = "home"
            songPage.state = "normal";
            songPage.focus = true;
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        }
    }

    Rectangle {
        id: background
        width: 800; height: 480
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#282828"
        clip: true

//        Image {
//            id: backgroundImage
//            width: 480
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.right: parent.right
//            sourceSize.height: 480
//            sourceSize.width: 480
//        }

        ChangingImage {
            id: backgroundImage
            width: 480
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            blur: true
            blurRadius: 4
            blurDeviation: 4
            blurSamples: 16
        }

//        GaussianBlur {
//            id: backgroundBlur
//            anchors.fill: backgroundImage
//            source: backgroundImage
//            radius: 4
//            deviation: 4
//            samples: 16
//        }

        Rectangle {
            height: 35
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            color: "white"
            opacity: .1
        }

        Image {
            id: backgroundImageOverlay
            anchors.fill: parent
            source: "../images/HomeBackground.png"
        }
    }

    Text {
        id: homeText
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 33
        font.family: "Segoe UI Light"
        font.bold: true
        font.pixelSize: 35
        color: "white"
        text: "Home"
    }

    ListModel {
        id: listModel
    }

    Component {
        id: listDelegate
        Item {
            width: 365; height: 43
            Text {
                anchors.left: parent.left
                anchors.leftMargin: 13
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -3
                font.family: "Segoe UI Light"
                font.pixelSize: 25
                font.bold: true
                color: "white"
                text: name
            }
        }
    }

    ListView {
        id: optionsUI
        anchors.left: parent.left
        anchors.leftMargin: 57
        anchors.top: parent.top
        anchors.topMargin: 100
        width: 365; height: 340
        clip: true
        model: listModel
        delegate: listDelegate
        highlight: Rectangle { color: "transparent"; border.color: "white"; border.width: 1 }
        spacing: 5
    }

}
