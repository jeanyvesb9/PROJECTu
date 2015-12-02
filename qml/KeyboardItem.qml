import QtQuick 2.0

Item {
    id: root
    width: 25; height: 25
    property bool selected
    property alias text: compText.text
    property int textVCOffset

    onSelectedChanged: {
        if (selected) {
            compRect.color = "white"
            compText.color = "black"
        }
        else {
            compRect.color = "transparent"
            compText.color = "white"
        }
    }

    Rectangle {
        id: compRect
        anchors.fill: parent
        color: "transparent"
        opacity: .9
    }

    Text {
        id: compText
        anchors.verticalCenter: compRect.verticalCenter
        anchors.verticalCenterOffset: textVCOffset
        anchors.horizontalCenter: compRect.horizontalCenter
        font.family: "Segoe UI Light"
        font.pixelSize:18
        font.bold: true
        color: "white"
    }
}
