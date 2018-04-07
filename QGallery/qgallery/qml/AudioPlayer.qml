import QtQuick 2.9
import QtMultimedia 5.9
import "components"

Rectangle {
    id: root
    anchors.centerIn: parent
    width: 360
    height: 150
    color: "#222222"

    Audio {
        id: playAudio
        source: "file:///home/tomoyuki/Data/music/01_Pierrot_Dancin.mp3"
        volume: 0.5
    }

    Controller {
        anchors.centerIn: parent
        playing: playAudio.playbackState === Audio.PlayingState

        onPlayClicked: playAudio.play()
        onPauseClicked: playAudio.pause()
        onStopClicked: playAudio.stop()
    }
}
