import QtQuick
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels

import iChat

Rectangle {
    Text {
        text: "hello world"
    }

    TreeVariantModel {
        id: treeVariantModel
        rows: {
            let init_data = [{
                                 "name": "aaaa",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "nnnnn",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "ddddd",
                                 "address": "NNNNNNNNNNN",
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
            let new_data = []
            for(let i =0;i<10;i++){
                for(let item of init_data){
                    new_data.push(item)
                }
            }

            return new_data
        }

        TreeColumn {
            display: "name"
            label: "名字"
        }
        TreeColumn {
            display: "address"
            label: "地址"
        }
        TreeColumn {
            display: "address1"
            label: "地址1"
        }
//        Component.onCompleted: {
//            console.log(rows[0], rows[1], headers[0])
//            for(let row of rows){
//                console.log(row)
//            }
//        }
    }

    TreeModel {
        id: treeModel
        rows: {
            let init_data = [{
                                 "name": "aaaa",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "nnnnn",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "ddddd",
                                 "address": "NNNNNNNNNNN",
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
            let new_data = []
            for(let i =0;i<100;i++){
                for(let item of init_data){
                    new_data.push(item)
                }
            }

            return new_data
        }
        TreeColumn {
            display: "name"
            label: "名字"
        }
        TreeColumn {
            display: "address"
            label: "地址"
        }
        TreeColumn {
            display: "address1"
            label: "地址1"
        }
//        Component.onCompleted: {
//            console.log(rows[0], rows[1], headers[0])
//            for(let row of rows){
//                console.log(row)
//            }
//        }
    }
    TableModel {
        id: tableModel
        rows: {
            let init_data = [{
                                 "name": "aaaa",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "nnnnn",
                                 "address": "00000000000",
                                 "address1": "111111111111111111"
                             }, {
                                 "name": "ddddd",
                                 "address": "NNNNNNNNNNN",
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
            let new_data = []
            for(let i =0;i<100;i++){
                for(let item of init_data){
                    new_data.push(item)
                }
            }

            return new_data
        }
        TableModelColumn {
            display: "name"
        }
        TableModelColumn {
            display: "address"
        }
//        Component.onCompleted: {
//            console.log(rows[0], rows[1])
//            for(let row of rows){
//                console.log(row)
//            }
//        }
    }

//    TreeView {
//        anchors.fill: parent
//        anchors.topMargin: 30
//        columnSpacing: 20
//        Component.onCompleted: {
//            console.log(width, height)
//        }

//        model: treeModel
//        delegate: Rectangle {
//            id: treeDelegate
//            implicitWidth: padding + label.x + label.implicitWidth + padding
//            implicitHeight: label.implicitHeight * 1.5

//            readonly property real indent: 20
//            readonly property real padding: 5

//            // Assigned to by TreeView:
//            required property TreeView treeView
//            required property bool isTreeNode
//            required property bool expanded
//            required property int hasChildren
//            required property int depth

//            TapHandler {
//                onTapped: treeView.toggleExpanded(row)
//            }

//            Text {
//                id: indicator
//                visible: treeDelegate.isTreeNode && treeDelegate.hasChildren
//                x: padding + (treeDelegate.depth * treeDelegate.indent)
//                anchors.verticalCenter: label.verticalCenter
//                text: "▸"
//                rotation: treeDelegate.expanded ? 90 : 0
//            }

//            Text {
//                id: label
//                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1)
//                                                        * treeDelegate.indent : 0)
//                //                width: treeDelegate.width - treeDelegate.padding - x
//                clip: true
//                text: display
//            }
//            //            Text {
//            //                id: label1
//            //                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1)
//            //                                                        * treeDelegate.indent : 0) + label.width
//            //                //                width: treeDelegate.width - treeDelegate.padding - x
//            //                clip: true
//            //                text: address
//            //            }
//        }
//    }

    TableView {
        anchors.fill: parent
//        anchors.topMargin: 300
        model: tableModel
        columnSpacing: 20

        ScrollBar.vertical: ScrollBar{

        }

        delegate: DelegateChooser {
            role: "display"
            DelegateChoice {
                column: 0
                roleValue: "aaaa"
                delegate: Text {
                    id: txt
                    color: "#ff0000"
                    text: display
                    Component.onCompleted: console.log(roleValue == display)
                }
            }
            DelegateChoice {
                column: 1
//                roleValue: "nnnnn"
                delegate: Text {
                    id: txt1
                    color: "#00ff00"
                    text: display
                }
            }
        }
    }
//    ListView {
//        width: 200; height: 400

//        ListModel {
//            id: listModel
//            ListElement { type: "info" }
//            ListElement { type: "switch" }
//            ListElement { type: "swipe" }
//            ListElement { type: "switch" }
//        }

//        DelegateChooser {
//            id: chooser
//            role: "type"
//            DelegateChoice { roleValue: "info"; ItemDelegate {  } }
//            DelegateChoice { roleValue: "switch"; SwitchDelegate {  } }
//            DelegateChoice { roleValue: "swipe"; SwipeDelegate {  } }
//        }

//        model: listModel
//        delegate: chooser
//    }
}
