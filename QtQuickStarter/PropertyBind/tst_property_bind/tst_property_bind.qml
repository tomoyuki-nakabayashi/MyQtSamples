import QtQuick 2.0
import QtTest 1.1
import "../"

PropertyBind {
    id: propertybind

    TestCase {
        name: "PropertyBind"
        function test_default_size() {
            compare(propertybind.contentHeight, 160*0.3*1.1)
        }
    }
}
