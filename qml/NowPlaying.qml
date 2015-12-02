import QtQuick 2.4
import QtQml 2.2
import QtGraphicalEffects 1.0
import custom 1.0
import "PlayFunctions.js" as PlayFunctions

Item {
    id: root
    width: 800; height: 480

    property string songName
    property string songArtist
    property string songAlbum
    property int songDuration
    property int songPlayed
    property int repeatMode // 0 = No ; 1 = All ; 2 = Song
    property int shuffleMode
    property int playStatus
    property int menuSelected
    property string backgroundUrl
    property string artworkUrl

    property string from

    signal playPause()
    signal previousSong()
    signal nextSong();

    Keys.onSpacePressed: playPause()

    Timer {
        id: timer
        interval: 1000; running: false; repeat: true
        onTriggered: playStatusUpdate.plusOneSecond();
    }

    onPlayStatusChanged: {
        if(playStatus === PlayStatusUpdate.Playing) {
            timer.start();
        }
        else {
            timer.stop();
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; anchors.horizontalCenterOffset: 800 }
            PropertyChanges { target: songText; opacity: 1 }
            PropertyChanges { target: progressBarSection; opacity: 1 }
            PropertyChanges { target: optionMenu; width: 0 }
            PropertyChanges { target: backgroundImage; bright: -0.25 }
            PropertyChanges { target: root; menuSelected: 0 }
        },

        State {
            name: "normal"
            PropertyChanges { target: root; anchors.horizontalCenterOffset: 0 }
            PropertyChanges { target: songText; opacity: 1 }
            PropertyChanges { target: progressBarSection; opacity: 1 }
            PropertyChanges { target: optionMenu; width: 0 }
            PropertyChanges { target: backgroundImage; bright: -0.25 }
            PropertyChanges { target: root; menuSelected: 0 }
        },

        State {
            name: "optionMenu"
            PropertyChanges { target: songText; opacity: 0 }
            PropertyChanges { target: progressBarSection; opacity: 0 }
            PropertyChanges { target: optionMenu; width: 451 }
            PropertyChanges { target: backgroundImage; bright: -0.7 }
        }
    ]

    transitions: [
        Transition {
            id: normal_TO_optionMenu
            from: "normal"; to: "optionMenu"; reversible: false
            NumberAnimation {
                id: d
                target: backgroundImage
                properties: "bright"
                duration: 300
                easing.type: Easing.OutExpo
            }
            NumberAnimation {
                id: dd
                target: optionMenu
                properties: "width"
                duration: 250
                easing.type: Easing.OutExpo
            }
        },

        Transition {
            id: optionMenu_TO_normal
            from: "optionMenu"; to: "normal"; reversible: false
            NumberAnimation {
                target: backgroundImage
                properties: "bright"
                duration: 300
                easing.type: Easing.OutExpo
            }
            NumberAnimation {
                target: optionMenu
                properties: "width"
                duration: 250
                easing.type: Easing.OutExpo
            }
        },

        Transition {
            id: hidden_TO_normal
            from: "hidden"; to: "normal"; reversible: false
            NumberAnimation {
                target: root
                properties: "anchors.horizontalCenterOffset"
                duration: 350
                easing.type: Easing.OutExpo
            }
        },

        Transition {
            id: normal_TO_hidden
            from: "normal"; to: "hidden"; reversible: false
            NumberAnimation {
                target: root
                properties: "anchors.horizontalCenterOffset"
                duration: 350
                easing.type: Easing.OutExpo
            }
        }
    ]
    
    Keys.onReturnPressed: {
        if (state == "normal") {
            state = "optionMenu";
        }
        else if (state == "optionMenu") {
            switchMenuSelectedFocus();
        }
    }

    Keys.onEscapePressed: {
        if (state == "normal") {
            state = "hidden";
            switch (from) {
            case "home":
                home.focus = true;
            }
            state = "hidden";
        }
        else if (state == "optionMenu") {
            state = "normal";
        }
    }

    Keys.onRightPressed: {
        if (state == "normal") {
            nextSong();
        }
        else if (state == "optionMenu") {
            if (menuSelected == 5) {
                //play sound
                //pass
            }
            else {
                menuSelected++;
            }
        }
    }

    Keys.onLeftPressed: {
        if (state == "normal") {
            previousSong();
        }
        else if (state == "optionMenu") {
            if (menuSelected == 0) {
                //play sound
                //pass
            }
            else {
                menuSelected--;
            }
        }
    }

    function switchMenuSelectedFocus() {
        switch (menuSelected) {
        case 0:
            optionMenuRepeat.focus = true;
            break;
        case 1:
            optionMenuShuffle.focus = true;
            break;
        case 2:
            optionMenuAddToPlaylist.focus = true;
            break;
        case 3:
            optionMenuHidden.focus = true;
            break;
        case 4:
            optionMenuEqualizer.focus = true;
            break;
        case 5:
            optionMenuFile.focus = true;
            break;
        }
    }

    Rectangle {
        id: screen
        anchors.fill: parent
        clip: true

        Item {
            id: background
            anchors.centerIn: parent
            width: 1250; height: 1167

            ChangingImage {
                id: backgroundImage
                anchors.fill: parent
                source: backgroundUrl
                blur: true
                blurRadius: 35
                blurDeviation: 17
                blurSamples: 33
                brightness: true
                bright: -0.25
            }
        }

        Item {
            id: artwork
            width: 250; height: 250
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 50

            Image {
                id: artworkCover
                anchors.horizontalCenter: artwork.horizontalCenter
                anchors.verticalCenter: artwork.verticalCenter
                source: "../images/Album-Cover.png"
            }

            ChangingImage {
                id: artworkImage
                anchors.fill: parent
                source: artworkUrl
            }

            Image {
                id: artworkDiagonalShine
                anchors.fill: artwork
                source: "../images/Diagonal-Shine.png"

            }
        }

        Item {
            id: songText
            width: 440; height: 90
            anchors.left: parent.left
            anchors.leftMargin: 340
            anchors.top: parent.top
            anchors.topMargin: 115
            Text {
                id: uiSongName
                anchors.top: parent.top
                anchors.topMargin: -13
                anchors.left: parent.left
                anchors.right: parent.right
                font.family: "Segoe UI"
                font.weight: Font.Light
                font.pixelSize: 40
                color: "white"
                opacity: 0.8
                text: songName
                elide: Text.ElideRight
            }

            Text {
                id: uiSongArtist
                anchors.top: uiSongName.bottom
                anchors.topMargin: 4
                anchors.left: parent.left
                anchors.leftMargin: 2
                anchors.right: parent.right
                font.family: "Segoe UI Light"
                font.pixelSize:21
                font.bold: true
                color: "white"
                opacity: 0.5
                text: songArtist
                elide: Text.ElideRight
            }

            Text {
                id: uiSongAlbum
                anchors.top: uiSongArtist.bottom
                anchors.topMargin: -5
                anchors.left: parent.left
                anchors.leftMargin: 2
                anchors.right: parent.right
                font.family: "Segoe UI Light"
                font.pixelSize:21
                font.bold: true
                color: "white"
                opacity: 0.5
                text: songAlbum
                elide: Text.ElideRight
            }
        }

        Item {
            id: progressBarSection
            width: 440; height: 70
            anchors.top: parent.top
            anchors.topMargin: 300
            anchors.left: artwork.right
            anchors.leftMargin: 40

            Image {
                id: playIcon
                anchors.top: progressBarSection.top
                anchors.left: progressBarSection.left
                anchors.leftMargin: 4
                source: "../images/Play.png"
                visible: playStatus === PlayStatusUpdate.Playing
            }

            Image {
                id: loadingIcon
                anchors.top: progressBarSection.top
                anchors.topMargin: -3
                anchors.left: progressBarSection.left
                anchors.leftMargin: 0
                source: "../images/Loading.png"
                visible: playStatus === PlayStatusUpdate.Loading
            }

            Image {
                id: pauseIcon
                anchors.top: progressBarSection.top
                anchors.left: progressBarSection.left
                anchors.leftMargin: 3
                source: "../images/Pause.png"
                visible: playStatus === PlayStatusUpdate.Paused
            }

            Text {
                id: uiSongPlayed
                anchors.top: progressBarSection.top
                anchors.topMargin: -10
                anchors.left: progressBarSection.left
                anchors.leftMargin: 32
                font.family: "Segoe UI Light"
                font.pixelSize: 21
                font.bold: true
                color: "white"
                text: PlayFunctions.calcSongPlayedString(songPlayed)

            }

            Text {
                id: uiSongLeft
                anchors.top: progressBarSection.top
                anchors.topMargin: -10
                anchors.right: progressBarSection.right
                font.family: "Segoe UI Light"
                font.pixelSize: 21
                font.bold: true
                color: "white"
                text: PlayFunctions.calcSongRemString(songPlayed, songDuration)

            }

            Rectangle {
                id: progressBar
                height: 6; width: 440
                anchors.verticalCenter: progressBarSection.verticalCenter
                anchors.verticalCenterOffset: -5.5
                anchors.horizontalCenter: progressBarSection.horizontalCenter
                clip: true

                ChangingImage {
                    id: progressBarBackground
                    anchors.verticalCenter: progressBar.verticalCenter
                    anchors.verticalCenterOffset: -90
                    anchors.horizontalCenter: progressBar.horizontalCenter
                    anchors.horizontalCenterOffset: -160
                    width: 1250; height: 1167
                    source: backgroundUrl
                    blur: true
                    blurRadius: 45
                    blurDeviation: 20
                    blurSamples: 33
                }

                Image {
                    id: progress
                    anchors.verticalCenter: progressBar.verticalCenter
                    anchors.verticalCenterOffset: 1
                    anchors.left: progressBar.left
                    width: PlayFunctions.calcProgressBarPerc(songPlayed, songDuration)
                    source: "../images/Progress.png"
                }
            }

            Rectangle {
                id: reproductionMarker
                width: 3; height: 14
                anchors.left: progressBarSection.left
                anchors.leftMargin: PlayFunctions.calcProgressBarPerc(songPlayed, songDuration) - 1
                anchors.verticalCenter: progressBar.verticalCenter
                anchors.verticalCenterOffset: 1
                color: "white"
            }

            Item {
                id: shuffleRepeatIcons
                anchors.right: progressBarSection.right
                anchors.rightMargin: -22 //22
                anchors.bottom: progressBarSection.bottom
                anchors.bottomMargin: -30
                width: 150; height: 90

                Image {
                    id: shuffleImage
                    anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                    anchors.left: shuffleRepeatIcons.left
                    anchors.leftMargin: {
                        switch(repeatMode)
                        {
                        case 0:
                            return 5;
                        case 1:
                            return -10;
                        case 2:
                            return 0;
                        }
                    }

                    source: "../images/Shuffle.png"
                    opacity: .6
                }

                Text {
                    id: shuffleText
                    anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                    anchors.verticalCenterOffset: 0
                    anchors.left: shuffleImage.right
                    anchors.leftMargin: 4
                    font.family: "Segoe UI Light"
                    font.pixelSize: 15
                    font.bold: true
                    color: "white"
                    text: { shuffleMode == PlayStatusUpdate.ShuffleOn? "All" : "Off" }

                    opacity: .6
                }

                Image {
                    id: repeatImage
                    anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                    anchors.right: repeatText.left
                    anchors.rightMargin: 4
                    source: "../images/Repeat.png"
                    opacity: .6
                }

                Text {
                    id: repeatText
                    anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                    anchors.verticalCenterOffset: 0
                    anchors.right: shuffleRepeatIcons.right
                    anchors.rightMargin: 23
                    font.family: "Segoe UI Light"
                    font.pixelSize: 15
                    font.bold: true
                    color: "white"
                    text: {
                        switch(repeatMode)
                        {
                        case 0:
                            return "Off";
                        case 1:
                            return "Album";
                        case 2:
                            return "Song";
                        }
                    }
                    opacity: .6
                }
            }
        }

        Item {
            id: optionMenu
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 451

            Rectangle {
                id: optionMenuBackground
                anchors.fill: optionMenu
                color: "Black"
                opacity: .72
            }

            Rectangle {
                id: optionMenuSideLine
                anchors.left: optionMenu.left
                anchors.top: optionMenuBackground.top
                anchors.bottom: optionMenuBackground.bottom
                width: 5
                clip: true

                ChangingImage {
                    id: optionMenuSideLineImage
                    anchors.verticalCenter: optionMenuSideLine.verticalCenter
                    anchors.horizontalCenter: optionMenuSideLine.horizontalCenter
                    anchors.horizontalCenterOffset: 48.5
                    width: 1250; height: 1167
                    source: backgroundUrl
                    blur: true
                    blurRadius: 45
                    blurDeviation: 20
                    blurSamples: 33
                }
            }

            Rectangle {
                id: optionMenuSelected
                anchors.top: optionMenu.top
                anchors.topMargin: 97 + 48 * menuSelected
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 46
                clip: true

                ChangingImage {
                    id: optionMenuSelectedImage
                    anchors.verticalCenter: optionMenuSelected.verticalCenter
                    anchors.verticalCenterOffset: {
                        switch(menuSelected)
                        {
                        case 0:
                            return 120;
                        case 1:
                            return 72;
                        case 2:
                            return 24;
                        case 3:
                            return -24;
                        case 4:
                            return -72;
                        case 5:
                            return -120;
                        }
                    }
                    anchors.horizontalCenter: optionMenuSelected.horizontalCenter
                    anchors.horizontalCenterOffset: -176.5
                    width: 1250; height: 1167
                    source: backgroundUrl
                    blur: true
                    blurRadius: 45
                    blurDeviation: 20
                    blurSamples: 33
                }
            }

            OptionMenuItem {
                id: optionMenuRepeat
                anchors.top: optionMenu.top
                anchors.topMargin: 96
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "Repeat"
                options: ["Off", "Album", "Song"]
                optionSelected: repeatMode
                displayOption: true
                displayHorizontalMenu: true
                onOptionSelectedChanged: repeatMode = optionSelected
            }

            OptionMenuItem {
                id: optionMenuShuffle
                anchors.top: optionMenuRepeat.bottom
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "Shuffle"
                options: ["Off", "All"]
                optionSelected: shuffleMode === PlayStatusUpdate.ShuffleOn
                displayOption: true
                displayHorizontalMenu: true

                onOptionSelectedChanged: {
                    if(optionSelected)
                        shuffleMode = PlayStatusUpdate.ShuffleOn
                    else
                        shuffleMode = PlayStatusUpdate.ShuffleOff
                }
            }

            OptionMenuItem {
                id: optionMenuAddToPlaylist
                anchors.top: optionMenuShuffle.bottom
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "Add to Playlist"

                onFocusChanged: {
                    if (focus) { addToPlaylist.state = "shown"; addToPlaylist.from = "nowPlaying"}
                }
            }

            OptionMenuItem {
                id: optionMenuHidden
                anchors.top: optionMenuAddToPlaylist.bottom
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "Hidden"
            }

            OptionMenuItem {
                id: optionMenuEqualizer
                anchors.top: optionMenuHidden.bottom
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "Equalizer"
            }

            OptionMenuItem {
                id: optionMenuFile
                anchors.top: optionMenuEqualizer.bottom
                anchors.left: optionMenu.left
                anchors.leftMargin: 5
                width: 446; height: 48
                mainText: "File"
            }
        }
    }
}
