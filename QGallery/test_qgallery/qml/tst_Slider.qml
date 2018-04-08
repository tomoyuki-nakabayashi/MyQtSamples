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
        height: 16
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
            compare(spy.signalArguments[0][0], Math.ceil(100*50/100))
        }

        function test_click_border_of_slider() {
            mouseClick(slider, 90)
            compare(spy.count, 1)
            compare(spy.signalArguments[0][0], Math.ceil(100*95/100))
        }

        function test_drag_slider_handle() {
            mouseDrag(slider, slider.width/2, slider.height/2, 10, 10)
            compare(spy.count, 2)
            compare(spy.signalArguments[0][0], Math.ceil(100*60/100))
        }
    }
}
