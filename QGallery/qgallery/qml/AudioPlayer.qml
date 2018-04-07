import QtQuick 2.9
import QtMultimedia 5.9
import "components"

Rectangle {
    id: root
    anchors.centerIn: parent
    width: 200
    height: 200
    color: "#222222"

    Audio {
        id: playAudio
        source: "file:///home/tomoyuki/Data/music/01_Pierrot_Dancin.mp3"
        volume: 0.5
    }

    Row {
        anchors.centerIn: parent
        spacing: 5

        ImageButton {
            id: buttonPlay
            width: 70
            height: 50

            backImage: "resources/button_border.png"
            foreImage: "resources/button_play.png"

            onClicked: {
                if(root.state === "playing") {
                    playAudio.pause()
                } else {
                    playAudio.play()
                }
            }
        }

        ImageButton {
            id: buttonStop
            width: 70
            height: 50

            backImage: "resources/button_border.png"
            foreImage: "resources/button_stop.png"

            onClicked: playAudio.stop()
        }
    }

    states: [
        State {
            name: "playing"
            when: playAudio.playbackState === Audio.PlayingState
            PropertyChanges {
                target: buttonPlay
                foreImage: "resources/button_pause.png"

            }
        }
    ]
}
