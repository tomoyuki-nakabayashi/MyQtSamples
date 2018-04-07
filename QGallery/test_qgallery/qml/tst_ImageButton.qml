import QtQuick 2.9
import QtTest 1.1
import "../../qgallery/qml/components"

Rectangle {
    id: root
    width: 640
    height:480
    property bool imageButtonClicked: false

    ImageButton {
        id: imageButton
        anchors.centerIn: parent
        width: 70
        height: 50

        backImage: "../../qgallery/qml/resources/button_border.png"
        foreImage: "../../qgallery/qml/resources/button_play.png"

        onClicked: {
            root.imageButtonClicked = true
        }
    }

    TestCase {
        name: "ImageButton"
        when: windowShown

        function test_can_handle_on_clicked_event() {
            compare(root.imageButtonClicked, false)

            mouseClick(imageButton)
            compare(root.imageButtonClicked, true)
        }

        function test_change_color_when_mouse_is_hovering() {
            mouseMove(imageButton, imageButton.width/2, imageButton.height/2)
            compare(imageButton.filterColor, imageButton.hoverColor)

            mouseMove(imageButton, -1, -1)
            compare(imageButton.filterColor, "#00000000")
        }

        function test_change_color_when_mouse_is_pressing() {
            mousePress(imageButton)
            compare(imageButton.filterColor, imageButton.pressedColor)

            mouseRelease(imageButton)
            compare(imageButton.filterColor, imageButton.hoverColor)
        }
    }
}
