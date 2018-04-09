import QtQuick 2.9
import QtMultimedia 5.9
import "components"

Rectangle {
    id: root
    anchors.centerIn: parent
    width: 360
    height: 400
    color: "#222222"

    Audio {
        id: playAudio
        volume: 0.5
        autoPlay: true
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

        onPositionRequested: {
            if(playAudio.playbackState === Audio.PlayingState) {
                playAudio.seek(position)
            }
        }
    }

    Controller {
        id: controller
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: information.bottom
        anchors.margins: 10

        playing: playAudio.playbackState === Audio.PlayingState

        onPlayClicked: playAudio.play()
        onPauseClicked: playAudio.pause()
        onStopClicked: playAudio.stop()
        onPreviousClicked: playAudio.source = contentsList.getPrevious()
        onNextClicked: playAudio.source = contentsList.getNext()
    }

    ContentsList {
        id: contentsList
        anchors.top: controller.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10

        onSelected: {
            playAudio.source = filePath
        }

        Component.onCompleted: {
            folder = "file:///home/tomoyuki/Data/music/"
        }
    }
}
