//好友总页面
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    implicitHeight: column.implicitHeight
    implicitWidth: column.implicitWidth

    ColumnLayout {
        id:column
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
                        notification.friendnotification.show()
                        notification.friendnotification.raise()
                        notification.friendnotification.requestActivate()
                    }
                }
            }
        }

        // 分割线
        Rectangle {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 1
            color: "#E6E6E6"
        }

        // 好友列表
        ListView {
            id: friendlist
            model: listModel
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height

            delegate: Friendlist {
                height: parent.height
                width: notification.width
                friendlist_text.text: model.text
            }
        }

        ListModel {
            id: listModel
            ListElement {
                text: "我的好友"
            }
        }
    }
}

