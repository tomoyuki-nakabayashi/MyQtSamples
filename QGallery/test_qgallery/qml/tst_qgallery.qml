import QtQuick 2.9
import QtTest 1.1
import QtMultimedia 5.9
import "../../qgallery/qml"

Rectangle {
    width: 640
    height: 480

    AudioPlayer {
        id: audioPlayer
    }

    TestCase {
        name: "AudioPlaer"
        when: windowShown

        function test_initial_state_is_null() {
            compare(audioPlayer.state, "")
        }

        function test_state_changes_by_click() {
            mouseClick(audioPlayer)
            compare(audioPlayer.state, "playing")

            mouseClick(audioPlayer)
            compare(audioPlayer.state, "")
        }
    }
}
