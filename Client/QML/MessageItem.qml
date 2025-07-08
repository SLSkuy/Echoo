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
    property var thisChatWidget
    property bool hovered: false
    property alias receivername: messageItem.nickname
    property alias unreadCountContainer :_unreadCountContainer

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
            // visible: true
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
            } else {
                if(!chatWidget) {
                    var component2 = Qt.createComponent("ChatWidget.qml");
                    if (component2.status === Component.Ready) {
                        chatWidget = component2.createObject(null, {
                            flags: Qt.Window | Qt.FramelessWindowHint, account:messageid, receiver:nickname
                        });
                    }
                    thisChatWidget=chatWidget;
                    chatWidget.topBar.toptext = messageItem.nickname
                }

                chatWidget.show();
                chatWidget.raise();
                chatWidget.requestActivate();

            }


            unreadCount.text = "0"
        }

    }
    function onClearunreadcount(){
        unreadCount.text = "0"
    }

    // 分割线
    Rectangle {
        width: parent.width
        height: 1
        color: "#E6E6E6"
        anchors.bottom: parent.bottom
    }

    // Connections {
    //     target: EchooClient
    //     function onMessageReceived(msg) {
    //         lastMessage = msg.content;
    //         unreadCount.text = "1";
    //         time = msg.timestamp
    //         console.log("ddd")
    //         console.log(msg.timestamp)
    //          console.log(time)

    //     }
    //     function onImgReceived(msg){
    //         lastMessage = msg[msg.length-1].content;
    //         unreadCount.text = "1";
    //         time = msg[msg.length-1].timestamp
    //     }
    //     function onTriggerMessage(receiverAccount, content){
    //         lastMessage = content
    //         time = new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss")
    //     }
    // }
    Connections {
        target: EchooClient

        function onRemoveMessagList(user){
            var account=user.account;
            for (var i = 0; i < messagetotal.messagelistModel.count; i++) {
                var item = messagetotal.messagelistModel.get(i);
                if (item.account === account) {
                    if(thisChatWidget)
                        thisChatWidget.close();
                    messagetotal.messagelistModel.remove(i);
                    break;
                }
            }
        }
    }
}
