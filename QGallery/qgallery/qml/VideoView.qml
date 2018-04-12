import QtQuick 2.9
import QtMultimedia 5.9

Video {
    id: root
    volume: 0.5
    autoPlay: true
    source: ""

    onSourceChanged: {
        if (source.toString().length > 0) {
            visible = true
        } else {
            visible = false
        }
    }

    Rectangle {
        anchors.fill: parent
        z: -1
        color: "#000000"
        opacity: 0.8

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
            onWheel: wheel.accepted = true

            onClicked: {
                if (mouse.button === Qt.RightButton) {
                    root.source = ""
                }
            }
        }
    }
}
