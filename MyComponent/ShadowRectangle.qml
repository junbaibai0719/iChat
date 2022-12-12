import QtQuick

Item {
    property alias color: rectangle.color
    property real shadowWidth: 0
    anchors.margins: shadowWidth
    anchors.fill: parent

    BorderImage {
        anchors.fill: rectangle
        anchors.margins: -shadowWidth
        border {
            left: shadowWidth
            top: shadowWidth
            right: shadowWidth
            bottom: shadowWidth
        }
        source: "qrc:/icons/shadow.png"
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
    }
}
