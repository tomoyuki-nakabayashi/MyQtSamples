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
        source: "file:///home/tomoyuki/Data/music/01 Glorious days.mp3"
        volume: 0.5
    }

    Information {
        id: information
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        title: toStr(playAudio.metaData.title)
        artist: toStr(playAudio.metaData.author)
        album: toStr(playAudio.metaData.albumTitle)

        position: playAudio.position
        duration: playAudio.duration
    }

    Controller {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: information.bottom
        anchors.margins: 10

        playing: playAudio.playbackState === Audio.PlayingState

        onPlayClicked: playAudio.play()
        onPauseClicked: playAudio.pause()
        onStopClicked: playAudio.stop()
    }
}
