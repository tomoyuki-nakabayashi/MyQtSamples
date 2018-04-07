import QtQuick 2.9

Column {
    id: root
    spacing: 5
    property alias title: title.text
    property string artist: ""
    property string album: ""

    property int position: 0
    property int duration: 0

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

    function formatSeconds(pos) {
        var date = new Date
        date.setTime(pos)
        return Qt.formatDateTime(date, "mm:ss")
    }

    function toStr(test) {
        return text === undefined ? " " : text
    }
}
