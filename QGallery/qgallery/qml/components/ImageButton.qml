import QtQuick 2.9

MouseArea {
    id: root
    hoverEnabled: true

    property alias backImage: backImage.source
    property alias foreImage: foreImage.source
    property alias caption: caption.text
    property alias captionColor: caption.color
    property alias captionFontSize: caption.font.pointSize

    property color pressedColor: "#ff0000"
    property color hoverColor: "#0000ff"

    BorderImage {
        id: backImage
        anchors.fill: parent
        border.top: 15
        border.left: 15
        border.right: 15
        border.bottom: 15

        Image {
            id: foreImage
            anchors.centerIn: parent
        }

        Text {
            id: caption
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: filter
        anchors.fill: parent
        radius: 15
        opacity: 0.2
        color: "transparent"
    }

    states: [
        State {
            name: "press"
            when: root.pressed
            PropertyChanges {
                target: filter
                color: root.pressedColor
            }
        },
        State {
            name: "hover"
            when: root.containsMouse
            PropertyChanges {
                target: filter
                color: root.hoverColor
            }
        }
    ]
}
