import QtQuick 2.9
import QtMultimedia 5.9

Rectangle {
    id: root
    width: 200
    anchors.centerIn: parent
    height: 200
    color: "#222222"

    Audio {
        id: playAudio
        source: "file:///home/tomoyuki/Data/music/01_Pierrot_Dancin.mp3"
        volume: 0.5
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: qsTr("Play")
        color: "#dddddd"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(root.state == "playing") {
                playAudio.pause()
            } else {
                playAudio.play()
            }
        }
    }

    states: [
        State {
            name: "playing"
            when: playAudio.playbackState === Audio.PlayingState
            PropertyChanges {
                target: text
                text: qsTr("Pause")

            }
        }
    ]
}
