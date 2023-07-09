import QtQuick

Text {
    signal clicked(var mouse)
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    color: {
        if (hovered) {
            return "#3E65FF"
        } else {
            return "#000"
        }
    }
    property bool hovered: false

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            cursorShape = Qt.PointingHandCursor
            parent.hovered = true
        }
        onClicked: e => {
                       parent.clicked(e)
                   }

        onExited: {
            parent.hovered = false
            cursorShape = Qt.ArrowCursor
        }
    }
}
