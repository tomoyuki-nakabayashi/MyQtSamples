import QtQuick 2.9
import "components"

Column {
    id: root
    spacing: 5
    property alias title: title.text
    property string artist: ""
    property string album: ""

    property int position: 0
    property int duration: 0

    signal positionRequested(int position)

    Text {
        id: title
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        color: "#deffff"
        font.pointSize: 16
        text: " "
    }

    Text {
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        color: "#deffff"
        font.pointSize: 9
        text: artist + " / " + album
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: formatSeconds(position) + " / " + formatSeconds(duration)
        color: "#deffff"
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 2

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: formatSeconds(position)
            color: "#deffff"
        }

        Slider {
            width: 150
            height: 16
            guideColor: "#deffff"
            handleColor: "#deffff"
            guideBkColor: "#00000000"
            handleBkColor: "#4e6f6f"
            min: 0
            max: duration
            position: root.position
            onHandleMoved: root.positionRequested(position)
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: formatSeconds(duration)
            color: "#deffff"
        }
    }

    function formatSeconds(pos) {
        var date = new Date
        date.setTime(pos)
        return Qt.formatDateTime(date, "mm:ss")
    }

    function toStr(test) {
        return text === undefined ? " " : text
    }
}
