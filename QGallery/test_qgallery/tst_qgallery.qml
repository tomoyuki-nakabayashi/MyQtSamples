import QtQuick 2.0
import QtTest 1.1
import "../qgallery/qml"

Rectangle {
    width: 640
    height: 480

    TestCase {
        name: "FirstTest"
        function test_first_test() {
            compare(0, 0)
        }
    }
}
