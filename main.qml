import QtQuick
import QtQuick.Controls

import componentLib

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr(" ")
    color: "#00000000"
    flags: flags | Qt.FramelessWindowHint
    minimumWidth: 200
    property int shellWidth: 6
    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal()
        } else {
            window.showMaximized()
        }
    }

    ShadowRectangle {
        parent: bordMouseArea
        shadowWidth: shellWidth
        Row {
            id: header
            width: parent.width
            height: 30
            z:100
            Component.onCompleted: console.log(spacing, parent.width, parent)
            MouseArea {
                width: parent.width - 3 * (minimizedBtn.width + parent.spacing)
                height: parent.height
                acceptedButtons: Qt.LeftButton
                onPressed: window.startSystemMove()
                onDoubleClicked: toggleMaximized()
                Component.onCompleted: console.log(
                                           3 * (minimizedBtn.width + parent.spacing))
            }
            FlatButton {
                id: minimizedBtn
                width: 32
                height: 24
                icon {
                    width: 12
                    height: 12
                    source: "qrc:/icons/window-minimize.svg"
                }
                onClicked: window.showMinimized()
            }
            FlatButton {
                id: maximizedBtn
                width: 32
                height: 24
                icon {
                    width: 12
                    height: 12
                    source: "qrc:/icons/window-maximize.svg"
                }
                onClicked: toggleMaximized()
            }
            FlatButton {
                id: closedBtn
                width: 32
                height: 24
                highlightColor: "#fb4d3f"
                icon {
                    width: 12
                    height: 12
                    source: "qrc:/icons/close-bold.svg"
                }

                onClicked: window.close()
            }
        }
        StackView {
            id:	body
            anchors.fill: parent
            contentItem: Rectangle {
                Text{
                    text: "hello world"
                }
            }
        }
    }
    MouseArea {
        id: bordMouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        //        propagateComposedEvents: true
        property var initWH: Qt.point(width, height)
        cursorShape: {
            const p = Qt.point(mouseX, mouseY)
            const radius = Math.pow(Math.pow(shellWidth, 2) * 2, 0.5)

            if (p.x < radius && p.y < radius) {
                return Qt.SizeFDiagCursor
            }
            if (p.x >= initWH.x - radius && p.y >= initWH.y - radius) {
                return Qt.SizeFDiagCursor
            }
            if (p.x >= initWH.x - radius && p.y < radius) {
                return Qt.SizeBDiagCursor
            }
            if (p.x < radius && p.y >= initWH.y - radius) {
                return Qt.SizeBDiagCursor
            }
            if (p.x < shellWidth || p.x >= initWH.x - shellWidth) {
                return Qt.SizeHorCursor
            }
            if (p.y < shellWidth || p.y >= initWH.y - shellWidth) {
                return Qt.SizeVerCursor
            }
        }
        onPositionChanged: initWH = Qt.point(width, height)

        onPressed: e => {
                       initWH = Qt.point(width, height)
                       let flag = 0
                       if (e.x < shellWidth) {
                           flag |= Qt.LeftEdge
                       }
                       if (e.x >= width - shellWidth) {
                           flag |= Qt.RightEdge
                       }
                       if (e.y < shellWidth) {
                           flag |= Qt.TopEdge
                       }
                       if (e.y >= height - shellWidth) {
                           flag |= Qt.BottomEdge
                       }
                       if (flag) {
                           window.startSystemResize(flag)
                       }
                       e.accepted = false
                   }
    }
}
