import QtQuick
import QtQuick.Controls

Button {
    id: control
    property string highlightColor: "#ebeced"
    flat: true
    hoverEnabled: true
    padding: 0
    spacing: 0
    horizontalPadding: 0
    verticalPadding: 0

    contentItem: Rectangle {

        implicitWidth: control.width
        implicitHeight: control.height
        color: control.hovered ? highlightColor : "#ffffff"
        Image {
            id: name
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: control.icon.width
            height: control.icon.height
            source: control.icon.source
        }
    }
}
