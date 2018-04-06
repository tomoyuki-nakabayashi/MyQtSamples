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

        function test_content_height() {
            verify(propertybind.contentHeight > 160*0.3*1.1)
            verify(propertybind.contentHeight < 160)

            propertybind.height = 540
            // bigger than 160
            verify(propertybind.contentHeight > 540*0.3*1.1)
            verify(propertybind.contentHeight < 540)
        }
    }
}
