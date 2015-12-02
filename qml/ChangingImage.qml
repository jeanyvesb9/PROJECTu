import QtQuick 2.3
import QtGraphicalEffects 1.0
Item {
    id: root
    property string source
    property bool blur
    property int blurRadius
    property int blurDeviation
    property int blurSamples
    property bool brightness
    property real bright

    readonly property int animationLenght: 200
    property bool _lastActive
    onSourceChanged: {
        if(!_lastActive) {
            image1.source = ""
            image1.source = source;
            _lastActive = true;
        }
        else {
            image0.source = ""
            image0.source = source;
            _lastActive = false;
        }
    }

    Item {
        id: image0Wrapper
        anchors.fill: parent

        Behavior on z {
            NumberAnimation { duration: animationLenght }
        }

        Image {
            id: image0
            anchors.fill: parent
            onStatusChanged: {
                if(status == Image.Ready) {
                    image0Black.opacity = 0;
                    image1Black.opacity = 1;
                    image0Wrapper.z = 100;
                    image1Wrapper.z = 0;
                }
            }
        }

        Loader {
            id: image0Blur
            anchors.fill: parent
            sourceComponent: if(blur) return imageBlur
            property Image img: image0
        }

        Loader {
            id: image0Bright
            anchors.fill: parent
            sourceComponent: if(brightness) return imageBrightness
            property Item img: blur? image0Blur.item : image0
        }

        Rectangle {
            id: image0Black
            anchors.fill: parent
            color: "black"
            opacity: 0
            Behavior on opacity {
                NumberAnimation { duration: animationLenght }
            }
        }
    }

    Item {
        id: image1Wrapper
        anchors.fill: parent

        Behavior on z {
            NumberAnimation { duration: animationLenght }
        }

        Image {
            id: image1
            anchors.fill: parent
            Behavior on opacity {
                NumberAnimation { duration: animationLenght }
            }
            onStatusChanged: {
                if(status == Image.Ready) {
                    image1Black.opacity = 0;
                    image0Black.opacity = 1;
                    image0Wrapper.z = 0;
                    image1Wrapper.z = 100;
                }
            }
        }

        Loader {
            id: image1Blur
            anchors.fill: parent
            sourceComponent: if(blur) return imageBlur
            property Image img: image1
        }

        Loader {
            id: image1Bright
            anchors.fill: parent
            sourceComponent: if(brightness) return imageBrightness
            property Item img: blur? image1Blur.item : image1
        }

        Rectangle {
            id: image1Black
            anchors.fill: parent
            color: "black"
            opacity: 0
            Behavior on opacity {
                NumberAnimation { duration: animationLenght }
            }
        }
    }

    Component {
        id: imageBlur
        GaussianBlur {
            id: gaussianBlur
            anchors.fill: parent
            source: img
            radius: blurRadius
            deviation: blurDeviation
            samples: blurSamples
        }
    }

    Component {
        id: imageBrightness
        BrightnessContrast {
            anchors.fill: parent
            source: img
            brightness: bright
        }
    }
}
