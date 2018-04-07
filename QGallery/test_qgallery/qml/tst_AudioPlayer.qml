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

        function test_dummy() {
            verify(true)
        }
    }
}
