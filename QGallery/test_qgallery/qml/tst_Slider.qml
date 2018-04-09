import QtQuick 2.9
import QtTest 1.1
import "../../qgallery/qml/components"

Rectangle {
    id: root
    width: 640
    height: 480
    property int position: 0

    Slider {
        id: slider
        anchors.centerIn: parent
        width: 100
        height: 20
        guideColor: "#deffff"
        handleColor: "#deffff"
        guideBkColor: "#00000000"
        handleBkColor: "#4e6f6f"
        min: 0
        max: 100
        position: root.position
    }

    SignalSpy {
        id: spy
        target: slider
        signalName: "handleMoved"
    }

    TestCase {
        name: "Slider"
        when: windowShown

        function init() {
            spy.clear()
        }

        function test_click_slider_area() {
            mouseClick(slider)
            compare(spy.count, 1)
            compare(spy.signalArguments[0][0], Math.ceil(100*45/90))
        }

        function test_click_border_of_slider() {
            mouseClick(slider, 90)
            compare(spy.count, 1)
            compare(spy.signalArguments[0][0], Math.ceil(100*85/90))
        }

        function test_drag_slider_handle() {
            mouseDrag(slider, slider.width/2, slider.height/2, 10, 0)
            compare(spy.count, 3)
            compare(spy.signalArguments[2][0], Math.ceil(100*55/90))
        }

        function test_handle_position() {
            root.position = 50
            // width*(position/max) - handle.width/2 + handle.x
            compare(slider.calcHandlePosition(), 45-8+5)
        }
    }
}
