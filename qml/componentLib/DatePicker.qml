import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootItem
    implicitWidth: 240
    implicitHeight: 30

    property var startDate: null
    property var endDate: null

    function pickDate(date) {
        if (startDate === null) {
            startDate = date
            endDate = null
        } else {
            if (endDate === null) {
                endDate = date
                calendar.close()
            } else {
                startDate = date
                endDate = null
            }
        }
        leftMonthGrid.startDate = startDate
        leftMonthGrid.endDate = endDate
        rightMonthGrid.startDate = startDate
        rightMonthGrid.endDate = endDate
    }

    Rectangle {
        anchors.fill: parent
        border.color: "#dcdfe6"
        radius: 4
        RowLayout {
            anchors.fill: parent
            HoverHandler {
                id: clearBtnHover
            }
            Text {
                Layout.leftMargin: 20
                Layout.preferredWidth: 80
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: rootItem.startDate === null ? "Grey" : "#000"
                text: {
                    if (rootItem.startDate === null) {
                        return qsTr("开始日期")
                    } else {
                        return Qt.formatDate(rootItem.startDate, "yyyy-MM-dd")
                    }
                }
            }
            Text {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("至")
            }
            Text {
                Layout.alignment: Qt.AlignRight
                Layout.preferredWidth: 80
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: rootItem.endDate === null ? "Grey" : "#000"
                text: {
                    if (rootItem.endDate === null) {
                        return qsTr("结束日期")
                    } else {
                        return Qt.formatDate(rootItem.endDate, "yyyy-MM-dd")
                    }
                }
            }
            Rectangle {
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                Layout.preferredWidth: 10
                Layout.preferredHeight: 10
                Text {
                    id: name
                    anchors.centerIn: parent
                    text: qsTr("x")
                    visible: clearBtnHover.hovered && endDate != null
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            startDate = null
                            endDate = null
                            leftMonthGrid.startDate = null
                            leftMonthGrid.endDate = null
                            rightMonthGrid.startDate = null
                            rightMonthGrid.endDate = null
                        }
                    }
                }
            }
        }
        TapHandler {
            onTapped: calendar.open()
        }
    }

    Popup {
        id: calendar
        y: parent.height

        implicitWidth: 660
        implicitHeight: 330

        property int leftMonth: 0
        property int rightMonth: 0
        property int leftYear: 0
        property int rightYear: 0

        Component.onCompleted: {
            var date = new Date()
            leftMonth = date.getMonth()
            leftYear = date.getFullYear()
            if (leftMonth < 11) {
                rightMonth = leftMonth + 1
                rightYear = leftYear
            } else {
                rightMonth = 0
                rightYear = leftYear + 1
            }
        }

        function monthChange(num) {
            if (leftMonth + num >= 0) {
                let year = Math.floor((leftMonth + num) / 12)
                leftMonth = (leftMonth + num) % 12
                leftYear += year
            } else {
                let year = Math.floor(Math.abs((leftMonth + num)) / 12)
                console.log(year)
                leftMonth = leftMonth + num + (year + 1) * 12
                leftYear -= (year + 1)
            }
            if (leftMonth < 11) {
                rightMonth = leftMonth + 1
                rightYear = leftYear
            } else {
                rightMonth = 0
                rightYear = leftYear + 1
            }
        }

        RowLayout {
            anchors.fill: parent
            spacing: 10

            ColumnLayout {
                id: leftDatePicker
                Layout.preferredHeight: parent.height
                Component.onCompleted: {
                    console.log(height, "column height")
                }

                RowLayout {
                    Layout.topMargin: 10
                    Layout.preferredWidth: parent.width
                    Link {
                        id: lastMonth
                        text: "<"
                        font.pointSize: 11

                        onClicked: e => {
                                       calendar.monthChange(-1)
                                   }
                    }
                    Text {
                        id: leftDatetimeStr
                        Layout.alignment: Qt.AlignCenter
                        text: calendar.leftYear + qsTr(
                                  "年") + (calendar.leftMonth + 1) + qsTr("月")

                        font.pointSize: 11
                    }
                }
                DayOfWeekRow {
                    locale: Qt.locale("zh_CN")

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                ElMonthGrid {
                    id: leftMonthGrid
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    month: calendar.leftMonth
                    year: calendar.leftYear
                    locale: Qt.locale("zh_CN")
                    onPickDate: function (date) {
                        rootItem.pickDate(date)
                    }
                }
            }
            Rectangle {
                Layout.preferredWidth: 1
                Layout.preferredHeight: parent.height
                border.color: "#dcdfe6"
            }

            ColumnLayout {
                id: rightDatePicker
                Layout.preferredHeight: parent.height
                RowLayout {
                    Layout.topMargin: 10
                    Layout.preferredWidth: parent.width
                    Component.onCompleted: {
                        console.log("right", width)
                    }

                    Text {
                        id: rightDatetimeStr
                        Layout.alignment: Qt.AlignCenter
                        text: calendar.rightYear + qsTr(
                                  "年") + (calendar.rightMonth + 1) + qsTr("月")

                        font.pointSize: 11
                    }
                    Link {
                        id: nextMonth
                        text: ">"
                        font.pointSize: 11

                        Layout.alignment: Qt.AlignRight
                        onClicked: e => {
                                       calendar.monthChange(1)
                                   }
                    }
                }
                DayOfWeekRow {
                    locale: Qt.locale("zh_CN")
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                ElMonthGrid {
                    id: rightMonthGrid
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    month: calendar.rightMonth
                    year: calendar.rightYear
                    locale: Qt.locale("zh_CN")
                    onPickDate: function (date) {
                        rootItem.pickDate(date)
                    }
                }
            }
        }
    }
}
