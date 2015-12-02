import QtQuick 2.4

Item {
    id: root
    width: 446; height: 48
    property alias mainText: mainText.text
    property bool displayOption
    property bool displayHorizontalMenu
    property var options: []
    property int optionSelected
    property int tempOption

    state: "normal"

    states: [
        State {
            name: "normal"
            PropertyChanges { target: arrow; opacity: .25 }
            PropertyChanges { target: currentOptionText; opacity: displayOption? 1 : 0 }
            PropertyChanges { target: hOptionMenu; anchors.rightMargin: -91 * options.length }
        },

        State {
            name: "horizontalMenu"
            PropertyChanges { target: arrow; opacity: 0 }
            PropertyChanges { target: currentOptionText; opacity: 0 }
            PropertyChanges { target: hOptionMenu; anchors.rightMargin: 0 }
        }

    ]

    transitions: [
        Transition {
            from: "normal"; to: "horizontalMenu"; reversible: false
            ParallelAnimation {
                NumberAnimation {
                    target: hOptionMenu
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutExpo
                }

                NumberAnimation {
                    target: currentOptionText
                    properties: "opacity"
                    duration: 50
                }

                NumberAnimation {
                    target: arrow
                    properties: "opacity"
                    duration: 50
                }
            }
        },

        Transition {
            from: "horizontalMenu"; to: "normal"; reversible: false
            ParallelAnimation {
                NumberAnimation {
                    target: hOptionMenu
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutExpo
                }

                NumberAnimation {
                    target: currentOptionText
                    properties: "opacity"
                    duration: 50
                }

                NumberAnimation {
                    target: arrow
                    properties: "opacity"
                    duration: 50
                }
            }
        }
    ]

    onFocusChanged: {
        if (state == "horizontalMenu") {
            state = "normal"
        }
        else if (state == "normal" && displayHorizontalMenu) {
            tempOption = optionSelected
            state = "horizontalMenu"
        }
    }

    Keys.onEscapePressed: {
        parent.focus = true;
    }

    Keys.onLeftPressed: {
        if (state == "normal") {
            //pass
        }
        else if (state == "horizontalMenu") {
            if (tempOption == 0) {
                //play sound
                //pass
            }
            else {
                tempOption--;
            }
        }
    }

    Keys.onRightPressed: {
        if (state == "normal") {
            //pass
        }
        else if (state == "horizontalMenu") {
            if (tempOption == (options.length - 1)) {
                //play sound
                //pass
            }
            else {
                tempOption++;
            }
        }
    }

    Keys.onReturnPressed: {
        if (state == "normal") {
            //TODO
        }
        else if (state == "horizontalMenu") {
            if (optionSelected != tempOption) {
                optionSelected = tempOption;
                parent.parent.state = "normal";
            }
            parent.focus = true;
        }
    }

    Item {
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: mainText
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -3
            anchors.left: parent.left
            anchors.leftMargin: 50
            font.family: "Segoe UI Light"
            font.pixelSize: 24
            font.bold: false
            color: "white"

        }

        Text {
            id: currentOptionText
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -1
            anchors.right: parent.right
            anchors.rightMargin: text == "Off"? 59 : 56
            font.family: "Segoe UI Light"
            font.pixelSize: 18
            font.bold: true
            color: "White"
            text: options.length? options[optionSelected] : ""

        }

        Image {
            id: arrow
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 21
            source: "../images/Arrow.png"

        }

        Item {
            id: hOptionMenu
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: 91 * options.length

            Rectangle {
                id: hOptionMenuBackground
                anchors.fill: parent
                color: "black"
                opacity: .5
            }

            Rectangle {
                id: hOptionMenuSelected
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: tempOption * 91
                width: 91
                color: "black"
                opacity: .55
                border.color: "white"
                border.width: 2

                Behavior on anchors.leftMargin {
                    NumberAnimation { duration: 10 } // Maybe 100???
                }
            }

            Row {
                id: hOptionMenuText
                anchors.fill: parent
                Repeater {
                    model: options

                    Item {
                        width: 91; height: 46
                        Text {
                            id: text
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: -1
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: 0
                            font.family: "Segoe UI Light"
                            font.pixelSize: 18
                            font.bold: true
                            text: modelData
                            color: "White"

                        }
                    }

                }
            }
        }
    }
}
