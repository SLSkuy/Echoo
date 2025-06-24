//单个消息列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    implicitHeight: row.implicitHeight
    implicitWidth: row.implicitWidth
    id: messageItem
    property string picture
    property string nickname
    property string lastMessage
    property string time
    property int unreadCount
    property bool isGroup: false
    property string messageid

    property bool hovered: false
    property alias receivername: messageItem.nickname
    color: hovered ? "#E6E6E6" : "transparent"

    RowLayout {
        id:row
        anchors.fill: parent
        spacing: 10

        // 头像
        Image {
            id: _picture
            Layout.preferredWidth: 50
            Layout.preferredHeight: 50
            Layout.leftMargin: 10
            source: messageItem.picture
        }

        // 消息内容
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 5

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredWidth: 100

                // 联系人名称
                Label {
                    id:_name
                    color: "black"
                    font.pixelSize: 16
                    font.bold: messageItem.unreadCount > 0
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    text: messageItem.nickname
                }

                // 时间
                Label {
                    id: _time
                    Layout.rightMargin: 10
                    text: messageItem.time
                    font.pixelSize: 12
                    color: "darkgrey"
                }
            }

            // 最后一条消息
            Label {
                id:_lastMessage
                font.pixelSize: 14
                color: "grey"
                Layout.fillWidth: true
                elide: Text.ElideRight
                text: messageItem.lastMessage
            }
        }

        // 未读消息计数
        Rectangle {
            id: _unreadCountContainer
            implicitHeight: 20
            implicitWidth: 20
            radius: 10
            color: "red"
            Layout.rightMargin: 10
            Layout.bottomMargin: 5
            visible: parseInt(messageItem.unreadCount.text) > 0 // 只有当未读消息数大于0时才显示

            Label {
                anchors.centerIn: parent
                id: _unreadCount
                color: "white"
                font.pixelSize: 12
                visible: false
                text: messageItem.unreadCount
            }
        }
    }

    HoverHandler {
        id: hoverHandler
        onHoveredChanged: messageItem.hovered = hovered
    }

    TapHandler {
        //设置初始值为null
        property var groupchat: null;
        property var chatWidget: null;
        onTapped: {
            if(isGroup){
                if(!groupchat) {
                    var component1 = Qt.createComponent("GroupChat.qml");
                    if (component1.status === Component.Ready) {
                        groupchat = component1.createObject(null, {
                            flags: Qt.Window | Qt.FramelessWindowHint, account:messageid, receiver:nickname
                        });

                    }
                }
                groupchat.show();
                groupchat.raise(); // 关键：置顶窗口
                groupchat.requestActivate(); // 激活窗口
                // groupchat.unreadCount.text = "0"; //点击进聊天界面就会让未读消息清零
            } else {
                if(!chatWidget) {
                    var component2 = Qt.createComponent("ChatWidget.qml");
                    if (component2.status === Component.Ready) {
                        chatWidget = component2.createObject(null, {
                            flags: Qt.Window | Qt.FramelessWindowHint, account:messageid, receiver:nickname
                        });
                    }
                    chatWidget.topBar.toptext = messageItem.nickname
                }

                chatWidget.show();
                chatWidget.raise();
                chatWidget.requestActivate();
                // chatWidget.unreadCount.text = "0"; //点击进聊天界面就会让未读消息清零
            }
            unreadCount.text = "0"
        }
    }


    // 分割线
    Rectangle {
        width: parent.width
        height: 1
        color: "#E6E6E6"
        anchors.bottom: parent.bottom
    }
}
