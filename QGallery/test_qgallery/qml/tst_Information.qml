import QtQuick 2.9
import QtMultimedia 5.9
import QtTest 1.1
import "../../qgallery/qml"

Rectangle {
    id: root
    width: 640
    height: 480

    Audio {
        id: playAudio
        source: "file:///home/tomoyuki/Data/music/nokia-tune.mp3"
        volume: 0.5
    }

    Information {
        id: information
        anchors.centerIn: parent

        title: "title"
        artist: "artist"
        album: "album"

        position: playAudio.position
        duration: playAudio.duration
    }

    TestCase {
        name: "Information"

        function init() {
            playAudio.stop()
        }

        function test_update_position() {
            compare(information.position, 0)

            playAudio.play()
            wait(1500)
            playAudio.pause()
            compare(information.formatSeconds(information.duration), "00:07")
            compare(information.formatSeconds(information.position), "00:01")
        }
    }
}
