import QtQuick 2.9
import QtTest 1.1
import "../../qgallery/qml"

Rectangle {
    id: root
    width: 640
    height: 480
    property bool playing: false

    Controller {
        id: controller
        anchors.centerIn: parent
        playing: root.playing
    }

    SignalSpy {
        id: spy
        target: controller
    }

    TestCase {
        name: "Controller"
        when: windowShown

        function init() {
            playing = false
            spy.clear()
        }

        function test_click_previous_button() {
            spy.signalName = "previousClicked"
            mouseClick(controller, 50/2, controller.height/2)

            spy.wait()
            compare(spy.count, 1)
        }

        function test_click_play_button() {
            spy.signalName = "playClicked"
            mouseClick(controller, 50+5+(70/2), controller.height/2)

            spy.wait()
            compare(spy.count, 1)
        }

        function test_click_pause_button() {
            playing = true
            spy.signalName = "pauseClicked"
            mouseClick(controller, 50+5+(70/2), controller.height/2)

            spy.wait()
            compare(spy.count, 1)
        }

        function test_click_stop_button() {
            spy.signalName = "stopClicked"
            mouseClick(controller, 50+5+70+5+(70/2), controller.height/2)

            spy.wait()
            compare(spy.count, 1)
        }

        function test_click_next_button() {
            spy.signalName = "nextClicked"
            mouseClick(controller, 50+5+70+5+70+5+(50/2), controller.height/2)

            spy.wait()
            compare(spy.count, 1)
        }

    }
}
