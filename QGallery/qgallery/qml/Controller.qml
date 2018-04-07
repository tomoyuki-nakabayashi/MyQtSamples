import QtQuick 2.9
import "components"

Row {
    id: root
    height: 50
    spacing: 5
    property bool playing: false

    signal previousClicked()
    signal playClicked()
    signal pauseClicked()
    signal stopClicked()
    signal nextClicked()

    ImageButton {
        id: buttonPrevious
        width: 50
        height: parent.height
        backImage: "resources/button_border.png"
        foreImage: "resources/button_previous.png"
        onClicked: root.previousClicked()
    }

    ImageButton {
        id: buttonPlay
        width: 70
        height: parent.height
        backImage: "resources/button_border.png"
        foreImage: "resources/button_play.png"
        onClicked: {
            if(playing) {
                root.pauseClicked()
            } else {
                root.playClicked()
            }
        }
    }

    ImageButton {
        id: buttonStop
        width: 70
        height: parent.height
        backImage: "resources/button_border.png"
        foreImage: "resources/button_stop.png"
        onClicked: root.stopClicked()
    }

    ImageButton {
        id: buttonNext
        width: 50
        height: parent.height
        backImage: "resources/button_border.png"
        foreImage: "resources/button_next.png"
        onClicked: root.nextClicked()
    }

    states: [
        State {
            name: "playing"
            when: playing
            PropertyChanges {
                target: buttonPlay
                foreImage: "resources/button_pause.png"
            }
        }
    ]
}
