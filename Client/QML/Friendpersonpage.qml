//好友个人页面

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow{
    property alias usernameFriend:_username
    // property alias sexFriend:_sex
    property alias signatureFriend:qm_nr
    property alias regionFriend:szd_nr
    property alias headPortraitFriend:tx
    property alias friendPersonpage: f_personpage

    id:f_personpage
    width:400
    height:300



    ColumnLayout{
        anchors.fill:parent

        Rectangle {
            id: titleBar
            Layout.preferredWidth: parent.width
            Layout.topMargin: 5
            Layout.alignment: Qt.AlignTop

            width: parent.width
            height: 40
            color: "transparent"  // 标题栏背景颜色

            RowLayout {
                anchors.fill: parent
                // spacing: 10

                // 窗口标题
                Text {
                    id:text
                    text: "个人主页"
                    color: "black"
                    font.pixelSize: 18
                    Layout.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                }

                Item {
                    Layout.fillWidth: true  // 占位符，将按钮推到右侧
                }

                // 最小化按钮
                Button {
                    id: minimizeButton
                    text: "—"

                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: f_personpage.showMinimized()
                    background: Rectangle {
                        color: "transparent"  // 设置背景颜色为透明
                        border.color: "transparent"  // 设置边框颜色为透明
                        border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // 最大化/还原按钮
                Button {
                    id: maximizeButton
                    text: f_personpage.visibility === Window.Maximized ? "r" : "+"
                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: {
                        if (f_personpage.visibility === Window.Maximized) {
                            f_personpage.showNormal()
                        } else {
                            f_personpage.showMaximized()
                        }
                    }
                    background: Rectangle {
                        color: "transparent"
                        border.color: "transparent"
                        border.width: 2
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // 关闭按钮
                Button {
                    id: closeButton
                    text: "x"
                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: f_personpage.close()
                    background: Rectangle {
                        color: "transparent"  // 设置背景颜色为透明
                        border.color: "transparent"  // 设置边框颜色为透明
                        border.width: 2
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        RowLayout{
            Rectangle {
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                width: 100
                height: 100
                radius: width / 2  // 使圆角半径等于宽度的一半
                color: "lightgrey"
                //后面改
                Image {
                    id: tx
                    anchors.fill:parent
                    source: friendheadPortrait.source
                    //TODO
                }
            }
            ColumnLayout{
                RowLayout{

                    Text{
                        id:_username
                        text:name.text
                    }
                    // Text{
                    //     id:_sex
                    //     text: "\u2640"
                    //     color:"pink"
                    // }
                }
                Text{
                    id:echoo_id
                    text:"id:"+friendpersonid

                    font.pixelSize: 20
                }
            }
        }
        RowLayout{
            Text{
                id:qm
                text:"签名"
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter
                visible: true

            }
            Rectangle{
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 61
                Text{
                    id:qm_nr
                    width:300
                    text:friendsign.text
                    font.pixelSize: 15
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    visible: true
                }
            }
        }
        RowLayout{
            Text{
                id:szd
                text:"所在地"
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter
                visible: false

            }
            Rectangle{
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 42
                Text{
                    id:szd_nr
                    text: friendregion
                    font.pixelSize: 15
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    visible: false

                }
            }
        }


    }

    Button{
        id:fsxx
        text:"发送消息"
        width:150
        anchors.bottom:parent.bottom
        anchors.bottomMargin:10
        anchors.right:parent.right
        anchors.rightMargin:10
        enabled: false

        //单机“发消息”按钮，弹出聊天框
        property var chatWidget: null;
        onClicked: {
            if(!chatWidget) {
                var component = Qt.createComponent("ChatWidget.qml");
                if (component.status === Component.Ready) {
                    chatWidget = component.createObject(null, {
                        flags: Qt.Window | Qt.FramelessWindowHint, account:echoo_id
                    });
                }
            }
            chatWidget.topBar.text11.text = usernameFriend.text
            chatWidget.show();
            chatWidget.raise(); // 关键：置顶窗口
            chatWidget.requestActivate(); // 激活窗口
            // unreadCount.text = "0"; //点击进聊天界面就会让未读消息清零
        }

    }

}
