import QtQuick 2.4
import QtGraphicalEffects 1.0

//IMPLEMENT AutoShift on first letter - LockedShift on DoubleReturn

Rectangle {
    id: root
    width: 705
    height: 130
    color: "black"
    border.color: "#CACBC7"
    border.width: 2
    opacity: .9

    property alias inputText: text.text
    property alias maximumLenght: text.maximumLength
    property string from
    property bool _isUpperCase: false
    property var _lowerCase: ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ',']
    property var _upperCase: ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'Ñ', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '¡', '!', '¿', '?', '(', ')', '-', '_', '/', '&', ':', ';']
    property int _keySelected
    property bool _selectionMode
    property int _lastSelection
    signal done()
    signal canceled()

    onFocusChanged: {
        if (focus){
            _keySelected = 0;
        }
        else {
            inputText = "";
            switch (from) {
            case "nowPlaying":
                nowPlaying.focus = true;
                return;
            }
        }
    }

    Keys.onLeftPressed: {
        if (!_selectionMode) {
            if (_keySelected > 0) {
                _keySelected--;
            }
            else {
                _keySelected = 43;
            }
        }
        else {
            text.cursorPosition--;
        }
    }

    Keys.onRightPressed: {
        if (!_selectionMode) {
            if (_keySelected < 43) {
                _keySelected++;
            }
            else {
                _keySelected = 0;
            }
        }
        else {
            text.cursorPosition++;
        }
    }

    Keys.onReturnPressed: {
        if (!_selectionMode) {
            if (_keySelected < 39) {
                if (_isUpperCase) {
                    text.insert(text.cursorPosition, _upperCase[_keySelected]);
                }
                else {
                    text.insert(text.cursorPosition, _lowerCase[_keySelected]);
                }
            }
            else if (_keySelected == 39) {
                text.insert(text.cursorPosition, ' ');
            }
            else if (_keySelected == 40){
                _isUpperCase = !_isUpperCase;
            }
            else if (_keySelected == 41) {
                _selectionMode = true;
            }
            else if (_keySelected == 42) {
                text.remove(text.cursorPosition, text.cursorPosition - 1);
            }
            else if (_keySelected == 43) {
                done();
            }
        }
        else {
            _selectionMode = false;
        }
    }

    Keys.onEscapePressed: {
        if (_selectionMode) {
            text.cursorPosition = _lastSelection;
            _selectionMode = false;
        }
        else {
            canceled();
        }
    }

    on_SelectionModeChanged: {
        _lastSelection = text.cursorPosition;
    }

    Rectangle {
        id: textField
        width: 675; height: 27
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "transparent"
        border.color: "#CACBC7"
        border.width: 1

        TextInput {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.right: parent.right
            font.family: "Segoe UI Light"
            font.pixelSize: 18
            font.bold: true
            color: "white"
            autoScroll: true
            verticalAlignment: TextInput.AlignVCenter
            cursorVisible: true
        }
    }

    Rectangle {
        id: keys
        width: 675; height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        color: "transparent"

        Flow {
            id: keysGrid
            anchors.fill: parent

            Repeater {
                id: keysRepeater
                model: 39

                KeyboardItem {
                    selected: _keySelected == index
                    text: _isUpperCase? _upperCase[index] : _lowerCase[index]
                    textVCOffset: {
                        if (!_isUpperCase) {
                            var a = [];
                            var b = [9, 11];
                            var c = [0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 13, 14, 18, 19, 20, 21, 22, 23, 24, 26];
                            var d = [15, 16, 17, 25];
                            var e = [6];

                            if (a.indexOf(index) != -1) {
                                return 0;
                            }
                            if (b.indexOf(index) != -1) {
                                return -1;
                            }
                            if (c.indexOf(index) != -1) {
                                return -2;
                            }
                            if (d.indexOf(index) != -1) {
                                return -3;
                            }
                            if (e.indexOf(index) != -1) {
                                return -4;
                            }
                        }
                        else {
                            return -1;
                        }
                        return 0;
                    }
                }
            }

            KeyboardItem {
                width: 75;
                text: "Space"
                selected: _keySelected == 39
            }

            KeyboardItem {
                width: 75; height: 25
                selected: _keySelected == 40

                Image {
                    id:keyShiftImg
                    sourceSize.width: 20
                    sourceSize.height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: _isUpperCase? "../images/ShiftOnArrow.png" : "../images/ShiftArrow.png"

                    opacity: .9
                }

                BrightnessContrast {
                    anchors.fill: keyShiftImg
                    source: keyShiftImg
                    brightness: -parent.selected
                }
            }

            KeyboardItem {
                width: 75; height: 25
                selected: _keySelected == 41

                Image {
                    id: keyCursorLeft
                    sourceSize.width: 15
                    sourceSize.height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -20
                    source: "../images/ShiftOnArrow.png"
                    rotation: -90
                    opacity: .9
                }

                Image {
                    id: keyCursorRight
                    sourceSize.width: 15
                    sourceSize.height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 20
                    source: "../images/ShiftOnArrow.png"
                    rotation: 90
                    opacity: .9
                }

                BrightnessContrast {
                    anchors.fill: keyCursorLeft
                    source: keyCursorLeft
                    brightness: -parent.selected
                    rotation: -90
                }

                BrightnessContrast {
                    anchors.fill: keyCursorRight
                    source: keyCursorRight
                    brightness: -parent.selected
                    rotation: 90
                }
            }

            KeyboardItem {
                width: 75; height: 25
                text: "Del"
                selected: _keySelected == 42
            }

            KeyboardItem {
                width: 75; height: 25
                text: "Ok"
                selected: _keySelected == 43
            }
        }
    }
}
