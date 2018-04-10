import QtQuick 2.9
import QtTest 1.1
import "../../qgallery/qml"

Rectangle {
    id: root
    width: 360
    height: 400
    color: "#222222"

    property var itemHeight: 35*1.1 + 5 // 5 is spacing
    property var testDataPath: "/home/tomoyuki/work/05.QtSamples/MyQtSamples/QGallery/test_qgallery/qml/data/"

    ContentsList {
        id: contentsList
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        folder: "file://" + root.testDataPath
    }

    SignalSpy {
        id: spy
        target: contentsList
        signalName: "selected"
    }

    TestCase {
        name: "ContentsList"
        when: windowShown

        function init() {
            // WA: Wait for loading directory contents.
            wait(100)
        }

        function test_click_first_mp3_item() {
            mouseClick(root, root.width/2, 2*itemHeight + 1)
            spy.wait()
            compare(spy.count, 1)
            compare(spy.signalArguments[0][0], contentsList.folder + "test1.mp3")
            compare(spy.signalArguments[0][1], 1)
        }

        function test_get_next() {
            mouseClick(root, root.width/2, 2*itemHeight + 1)
            spy.wait()
            compare(contentsList.getNext(), root.testDataPath + "test2.mp3")
            compare(contentsList.getNext(), root.testDataPath + "test3.mp3")
            compare(contentsList.getNext(), root.testDataPath + "test3.mp3")
        }

        function test_get_previous() {
            mouseClick(root, root.width/2, 4*itemHeight + 1)
            spy.wait()
            compare(contentsList.getPrevious(), root.testDataPath + "test2.mp3")
            compare(contentsList.getPrevious(), root.testDataPath + "test1.mp3")
            compare(contentsList.getPrevious(), root.testDataPath + "test1.mp3")
        }
    }
}
