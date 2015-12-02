import QtQuick 2.4
import "PlayFunctions.js" as PlayFunctions

Item {
    id: root
    property alias selected: listMenu.selectedOption
    property var playlists
    property string from
    signal added(int playlist)
    signal createNewPlaylist()

    function goBack( done ) {
        switch (from) {
        case "nowPlaying":
            nowPlaying.focus = true;
            if (done) {
                nowPlaying.state = "normal";
            }
            break;
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: listMenu; anchors.rightMargin: -800 }
            PropertyChanges { target: listMenu; focus: false }
        },
        State {
            name: "shown"
            PropertyChanges { target: listMenu; anchors.rightMargin: 0 }
            PropertyChanges { target: listMenu; focus: true }
        }
    ]

    ListMenu {
        id: listMenu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: -800
        width: 800
        title: "Add to Playlist"
        subtitle: "Select a playlist and press the knob"
        options: playlists.concat(["New Playlist"])

        Behavior on anchors.rightMargin {
            NumberAnimation { duration: 250; easing.type: Easing.OutExpo }
        }

        Keys.onEscapePressed: {
            root.state = "hidden"
            goBack(false)
        }

        Keys.onReturnPressed: {
            root.state = "hidden";
            goBack(true)
            if (selectedOption + 1 < options.length) {
                root.added(selectedOption);
            }
            else {
                root.createNewPlaylist();
            }
        }
    }
}
