import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480

    PropertyBind {
        id: propertybind
        anchors.centerIn: parent
        width: window.width
        height: window.height
    }
}
