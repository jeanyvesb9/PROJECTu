import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import custom 1.0

ApplicationWindow {
    title: qsTr("PROJECTu")
    id: window
    objectName: "rootMainItem"
    width: 800
    height: 480
    visible: true

    signal playStatusUpdateRequest(var revNumber)
    signal playPauseRequest()
    signal setDacpProperty(var name, var value)
    signal previousSongRequest()
    signal nextSongRequest()
    signal playSong()

    Item {
        id: root
        anchors.fill: parent
        HomePage {
            id: home
            anchors.fill: root
            image: playStatusUpdate.artworkUrl
            playing: true
            focus: true
            onPlay: { playSong() }
        }

        NowPlaying {
            id: nowPlaying
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            songName: playStatusUpdate.name
            songArtist: playStatusUpdate.artist
            songAlbum: playStatusUpdate.album
            songDuration: Math.round(playStatusUpdate.trackLenght / 1000)
            songPlayed: Math.round(playStatusUpdate.trackPlayed / 1000)
            artworkUrl: playStatusUpdate.artworkUrl
            backgroundUrl: playStatusUpdate.backgroundUrl
            repeatMode: {
                switch(playStatusUpdate.repeatStatus) {
                case PlayStatusUpdate.RepeatNone:
                    return 0;
                case PlayStatusUpdate.RepeatSingle:
                    return 2;
                case PlayStatusUpdate.RepeatAll:
                    return 1;
                }
            }
            onRepeatModeChanged: {
                switch(repeatMode) {
                case 0:
                    playStatusUpdate.repeatStatus = PlayStatusUpdate.RepeatNone;
                    break;
                case 1:
                    playStatusUpdate.repeatStatus = PlayStatusUpdate.RepeatAll;
                    break;
                case 2:
                    playStatusUpdate.repeatStatus = PlayStatusUpdate.RepeatSingle;
                    break;
                }
                setDacpProperty("dacp.repeatstate", playStatusUpdate.repeatStatus);
            }
            shuffleMode: playStatusUpdate.shuffleStatus
            onShuffleModeChanged: setDacpProperty("dacp.shufflestate", shuffleMode)
            playStatus: playStatusUpdate.playStatus
            state: "hidden"

            onPlayPause: playPauseRequest()
            onPreviousSong: previousSongRequest()
            onNextSong: nextSongRequest()
        }

        SongPage {
            id: songPage
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            state: "hidden";
        }

        AddToPlaylist {
            id: addToPlaylist
            anchors.fill: root
            playlists: ["Party", "Quiet", "Study", "Coding", "Movies", "Victorious", "Modern", "Old Hits"]

            onAdded: {

            }

            onCreateNewPlaylist: {

            }
        }

        StatusBarTop {
            id: statusBar
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            playStatus: playStatusUpdate.playStatus
            connectionType: 4
            opacity: 1
        }

        Keyboard {
            id: keyboard
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: focus? 0 : 350
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on anchors.verticalCenterOffset {
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.OutExpo
                }
            }

            onCanceled: {
                focus = false
            }
        }
    }
}
