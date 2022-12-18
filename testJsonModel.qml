import QtQuick
import Qt.labs.qmlmodels

import iChat

Rectangle {
    Text {
        text: "hello world"
    }
    TreeModel {
        id: treeModel
        rows: [{
                "name": "aaaa",
                "address": "00000000000",
                "address1": "111111111111111111"
            }, {
                "name": "nnnnn",
                "address": "00000000000",
                "address1": "111111111111111111"
            }, {
                "name": "ddddd",
                "address": "00000000000",
                "address1": "111111111111111111",
                "children": [{
                        "name": "222222222222",
                        "children": [{
                                "name": "........."
                            }]
                    }, {
                        "name": "333333333333333"
                    }]
            }]
        TreeColumn {
            prop: "name"
            label: "名字"
        }
        TreeColumn {
            prop: "address"
            label: "地址"
        }
        TreeColumn {
            prop: "address1"
            label: "地址1"
        }
        Component.onCompleted: {
            console.log(rows[0], rows[1], headers[0])
        }
    }
    TableModel {
        id: tableModel
        rows: treeModel.rows
        TableModelColumn {
            display: "name"
        }
        TableModelColumn {
            display: "address"
        }
    }

    TreeView {
        anchors.fill: parent
        anchors.topMargin: 30
        columnSpacing: 20
        Component.onCompleted: {
            console.log(width, height)
        }

        model: tableModel
        delegate: Item {
            id: treeDelegate
            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1.5

            readonly property real indent: 20
            readonly property real padding: 5

            // Assigned to by TreeView:
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth

            TapHandler {
                onTapped: treeView.toggleExpanded(row)
            }

            Text {
                id: indicator
                visible: treeDelegate.isTreeNode && treeDelegate.hasChildren
                x: padding + (treeDelegate.depth * treeDelegate.indent)
                anchors.verticalCenter: label.verticalCenter
                text: "▸"
                rotation: treeDelegate.expanded ? 90 : 0
            }

            Text {
                id: label
                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1)
                                                        * treeDelegate.indent : 0)
                //                width: treeDelegate.width - treeDelegate.padding - x
                clip: true
                text: display
            }
            //            Text {
            //                id: label1
            //                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1)
            //                                                        * treeDelegate.indent : 0) + label.width
            //                //                width: treeDelegate.width - treeDelegate.padding - x
            //                clip: true
            //                text: address
            //            }
        }
    }

    TableView {
        anchors.fill: parent
        anchors.topMargin: 300
        model: tableModel
        columnSpacing: 20
        delegate: DelegateChooser {
            role: "display"
            DelegateChoice {
                roleValue: "aaaa"
                delegate: Text {
                    id: txt
                    color: "#ff0000"
                    text: display
                }
            }
            DelegateChoice {
//                roleValue: "aaaa"
                delegate: Text {
                    id: txt1
                    color: "#00ff00"
                    text: display
                }
            }
        }
    }
}
