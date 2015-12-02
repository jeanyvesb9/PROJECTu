import QtQuick 2.4

Rectangle {
    id: root
    property string title: ""
    property string subtitle: ""
    property var options: []
    property alias selectedOption: optionsUI.currentIndex
    property bool showDescription: false
    property string selectedOptionDescription: ""

    color: "black"

    Keys.onLeftPressed: optionsUI.decrementCurrentIndex()
    Keys.onRightPressed: optionsUI.incrementCurrentIndex()

    Text{
        id: titleUI
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 30
        font.family: "Segoe UI light"
        font.pixelSize: 30
        font.bold: true
        color: "white"
        text: title

        opacity: .8
    }

    Text {
        id: subtitleUI
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 30
        font.family: "Segoe UI light"
        font.pixelSize: 20
        font.bold: true
        color: "white"
        text: subtitle

        opacity: .5
    }

    Rectangle {
        id: descriptionBox
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 740; height: 100
        color: "transparent"
        border.color: "white"
        border.width: 1
        opacity: showDescription? .7 : 0

        Text {
            id: descriptionUI
            anchors.left: parent.left
            anchors.leftMargin: 7
            anchors.top: parent.top
            font.family: "Segoe UI Light"
            font.pixelSize: 20
            color: "white"
            text: selectedOptionDescription

        }
    }

    Rectangle {
        id: optionsViewColumn
        anchors.right: parent.right
        anchors.rightMargin: 30
        y: 110 + optionsUI.visibleArea.yPosition * optionsUI.height
        width: 10
        height: optionsUI.visibleArea.heightRatio * optionsUI.height
        color: "white"
        opacity: .75
    }

    ListModel {
        id: listModel
    }

    onOptionsChanged: {
        listModel.clear();
        for (var i in options) {
            listModel.append({"name": options[i]});
        }
    }

    Component {
        id: listDelegate
        Item {
            width: 700; height: 48
            Text {
                anchors.left: parent.left
                anchors.leftMargin: 13
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -3
                font.family: "Segoe UI Light"
                font.pixelSize: 20
                font.bold: true
                color: "white"
                text: name

            }
        }
    }

    ListView {
        id: optionsUI
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 110
        width: 700; height: showDescription? 225 : 325
        clip: true
        model: listModel
        delegate: listDelegate
        highlight: Rectangle { color: "transparent"; border.color: "white"; border.width: 1 }
        spacing: 2
    }
}
