import QtQuick 2.4
import custom 1.0

Item {
    id: root
    width: 800; height: 35
    property int playStatus
    property int connectionType: 0 // 0 = None ; 1 = Ethernet ; 2 = Wifi-None ; 3 = Wifi-Low ; 4 = Wifi-Medium ; 5 = Wifi-High


    onConnectionTypeChanged: {
        switch(connectionType) {
        case 0:
            connection.visible = false;
            break;
        case 1:
            connection.visible = true;
            connection.source = "../images/StatusBar-Ethernet.png";
            break;
        case 2:
            connection.visible = true;
            connection.source = "../images/StatusBar-Wifi-N.png";
            break;
        case 3:
            connection.visible = true;
            connection.source = "../images/StatusBar-Wifi-L.png";
            break;
        case 4:
            connection.visible = true;
            connection.source = "../images/StatusBar-WiFi-M.png";
            break;
        case 5:
            connection.visible = true;
            connection.source = "../images/StatusBar-Wifi-H.png";
            break;
        }
    }

    Image {
        id: connection
        anchors.right: parent.right
        anchors.rightMargin: 21
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: play
        anchors.right: connection.left
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        source: "../images/StatusBar-Play.png"
        visible: playStatus === PlayStatusUpdate.Playing
    }

    Image {
        id: pause
        anchors.right: connection.left
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        source: "../images/Pause.png"
        opacity: .6
        visible: playStatus === PlayStatusUpdate.Paused
    }
}

