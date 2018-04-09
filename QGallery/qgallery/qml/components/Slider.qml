import QtQuick 2.9

Item {
    id: root
    width: 100
    height: 20

    property int max: 4
    property int min: 0
    property int position: 0

    property color guideColor: "#ffffff"
    property color handleColor: "#ffffff"
    property color guideBkColor: "#ffffff"
    property color handleBkColor: "#ffffff"
    property real radius: 0

    signal handleMoved(int position)

    Component.onCompleted: {
        setHandlePosition()
    }

    onPositionChanged: {
        setHandlePosition()
    }

    function setHandlePosition() {
        handle.x = calcHandlePosition()
    }

    function calcHandlePosition() {
        if (root.max != 0) {
            return ((guide.width * (root.position / root.max)) - (handle.width * 0.5) + guide.x)
        } else {
            return (-handle.width * 0.5 + guide.x)
        }
    }

    Rectangle {
        id: guide
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.5
        color: root.guideBkColor
        border.color: root.guideColor
        border.width: 1
        radius: root.radius

        MouseArea {
            anchors.fill: parent
            onClicked: root.handleMoved(calcPosition(mouse.x))
            onPositionChanged: root.handleMoved(calcPosition(mouse.x))

            function calcPosition(x) {
                var position = Math.ceil(root.max * x / guide.width)
                if (position > max) {
                    position = max
                } else if (position < min) {
                    position = min
                }
                return position
            }
        }
    }

    Rectangle {
        id: handle
        anchors.verticalCenter: parent.verticalCenter
        x: -width * 0.5 + guide.x
        width: height
        height: parent.height * 0.8
        color: root.handleBkColor
        border.color: root.handleColor
        border.width: 1
        radius: height * 0.5
    }
}
