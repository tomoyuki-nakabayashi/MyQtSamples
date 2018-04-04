import QtQuick 2.0
import QtTest 1.1
import "../"

PropertyBind {
    id: propertybind

    TestCase {
        name: "PropertyBind"
        function test_property_bind_width() {
            compare(propertybind.width, 360)
        }
    }
}
