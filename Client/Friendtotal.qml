// //好友列表

// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts


// Rectangle{

//     ColumnLayout{
//         anchors.fill: parent
//         Rectangle{
//             id:notification
//             property bool hovered
//             Layout.preferredWidth: parent.width
//             Layout.preferredHeight: 40
//             color: hovered ? "#E6E6E6" : "transparent"
//             Label{
//                 id:groupmessage
//                 text: " \n  好友通知\n"

//                 Layout.alignment: Qt.AlignCenter
//                 font.pixelSize: 16

//             }
//             HoverHandler {
//                 id: hoverHandler
//                 onHoveredChanged: notification.hovered = hovered
//             }
//             TapHandler{
//                 id:friendTaphandler
//                 property var friendnotification: null;
//                 onTapped: {
//                     if(!friendnotification) {
//                         var component = Qt.createComponent("Friendnotification.qml");
//                         if (component.status === Component.Ready) {
//                             friendnotification = component.createObject(null, {
//                                     flags: Qt.Window | Qt.FramelessWindowHint
//                             });
//                         }
//                     }
//                     friendnotification.show();
//                     friendnotification.raise(); // 关键：置顶窗口
//                     friendnotification.requestActivate(); // 激活窗口

//                 }
//             }


//         }

//         // 分割线
//         Rectangle {
//             width: parent.width
//             Layout.preferredWidth: parent.width
//             Layout.preferredHeight: 1
//             color: "#E6E6E6"
//         }

//         //列出
//         ListView {
//             id: friendlist
//             model: listModel
//             implicitWidth: parent.width
//             implicitHeight: parent.height

//             delegate:
//                 Friendlist{
//                     height:parent.height/listModel.count
//                     width: parent.width
//                     text.text: text1
//                 }

//         }

//         ListModel {
//             id: listModel
//             ListElement {
//                 text1:"我的好友"
//             }
//         }


//     }
// }


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {

    ColumnLayout {
        anchors.fill: parent

        // 好友通知标题栏
        Rectangle {
            id: notification
            property bool hovered
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 40
            color: hovered ? "#E6E6E6" : "transparent"

            // 在组件加载时创建窗口（但保持隐藏）
            property var friendnotification: Qt.createComponent("Friendnotification.qml").createObject(null, {
                flags: Qt.Window | Qt.FramelessWindowHint,
                visible: false  // 初始不可见
            })

            Label {
                id: groupmessage
                text: " \n  好友通知\n"
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 16
            }

            HoverHandler {
                id: hoverHandler
                onHoveredChanged: notification.hovered = hovered
            }

            TapHandler {
                onTapped: {
                    if (notification.friendnotification) {
                        notification.friendnotification.visible = true  // 点击时显示
                        notification.friendnotification.raise()
                        notification.friendnotification.requestActivate()
                    }
                }
            }
        }

        // 分割线
        Rectangle {
            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 1
            color: "#E6E6E6"
        }

        // 好友列表
        ListView {
            id: friendlist
            model: listModel
            implicitWidth: parent.width
            implicitHeight: parent.height

            delegate: Friendlist {
                height: parent.height / listModel.count
                width: parent.width
                text.text: text1
            }
        }

        ListModel {
            id: listModel
            ListElement {
                text1: "我的好友"
            }
        }
    }



}
