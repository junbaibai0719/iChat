import QtQuick
import QtQuick.Templates as T

T.AbstractMonthGrid {
    id: control

    implicitWidth: Math.max(
                       background ? background.implicitWidth : 0,
                       contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        background ? background.implicitHeight : 0,
                        contentItem.implicitHeight + topPadding + bottomPadding)

    property var startDate: null
    property var endDate: null
    signal pickDate(var date)

    //! [delegate]
    delegate: Rectangle {
        id: dayRect
        required property var model
        property bool hovered: false
        property int status: {
            if (control.startDate !== null && control.endDate !== null) {
                let s0 = null
                let s1 = null
                if (control.startDate < control.endDate) {
                    s0 = control.startDate
                    s1 = control.endDate
                } else {
                    s0 = control.endDate
                    s1 = control.startDate
                }
                if (model.date > s0 && model.date < s1) {
                    return 2
                }
            }

            if (control.startDate !== null && model.date.getTime(
                        ) === control.startDate.getTime()) {
                return 1
            }
            if (control.endDate !== null && model.date.getTime(
                        ) === control.endDate.getTime()) {
                return 1
            }
            return 0
        }

        implicitWidth: dayText.width + 12
        implicitHeight: dayText.height + 12

        color: {
            if (dayRect.status === 1) {
                return "#3E65FF"
            } else if (dayRect.status === 2) {
                return "#f2f6fc"
            }
            return "#fff"
        }
//        radius: 10


        Text {
            id: dayText
            anchors.centerIn: parent
            anchors.margins: 6
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            //        opacity: model.month === control.month ? 1 : 0
            color: {
                if (dayRect.status === 1) {
                    return "#fff"
                } else if (hovered) {
                    return "#3E65FF"
                } else if (model.month !== control.month) {
                    return "#dcdfe6"
                } else {
                    return "#000"
                }
            }

            text: model.day
            font: control.font
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor
                parent.hovered = true
            }

            onExited: {
                parent.hovered = false
                cursorShape = Qt.ArrowCursor
            }

            onClicked: {
                control.pickDate(model.date)
            }
        }
    }

    //! [delegate]

    //! [contentItem]
    contentItem: Grid {
        rows: 6
        columns: 7
        rowSpacing: control.spacing
        columnSpacing: control.spacing

        Repeater {
            model: control.source
            delegate: control.delegate
        }
    }
    //! [contentItem]
}
