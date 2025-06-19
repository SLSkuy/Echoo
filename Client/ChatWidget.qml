import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Window

FrameLessWindow {
    property alias topBar: topbar
    id:chatwidget
    visible: true
    width: 800
    height: 600
    title: "QQ聊天窗口"


    // 主布局
    Column {
        id:column
        anchors.fill: parent

        //titlebar
        TopBar{
            id:topbar

        }
        // 顶部工具栏
        ToolBar {
            id:toolbar
            // anchors.topMargin:10
            background: Rectangle {
                color: "white"  // 设置背景颜色为白色
            }
            anchors.right:parent.right
            // anchors.bottomMargin:80
            RowLayout {

                anchors.fill: parent
                Item {
                    Layout.fillWidth: true  // 占位符，将按钮推到右侧
                }
                // 发起群聊按钮
                Button {
                    // text:"add"
                    text: "🤝"
                    ToolTip {
                        id: buttonTooltip
                        text: "发起群聊"
                        visible: parent.hovered
                        delay: 500 // 悬停500毫秒后显示
                    }

                    // 启用悬停检测
                    hoverEnabled: true
                    onClicked: {
                        // 实现发起群聊的逻辑
                        console.log("发起群聊");

                        var component  = Qt.createComponent("SelectFriends.qml");
                        if (component.status === Component.Ready) {
                            var selectfirends = component.createObject(parent);
                            selectfirends.show();

                        }
                    }
                    background: Rectangle {
                        color: "white"  // 设置背景颜色为白色
                        border.color: "white"  // 设置边框颜色为白色
                        border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }



                // 更多按钮（删除好友）
                Button {
                    // text:"more"
                    text: "\u{1F5D1}"
                    ToolTip {
                        id: buttonTooltip1
                        text: "删除好友"
                        visible: parent.hovered
                        delay: 500 // 悬停500毫秒后显示
                    }

                    // 启用悬停检测
                    hoverEnabled: true
                    onClicked: {
                        // 实现更多的逻辑
                        console.log("删除好友");

                    }
                    background: Rectangle {
                        color: "white"  // 设置背景颜色为白色
                        border.color: "white"  // 设置边框颜色为白色
                        border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
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

        Rectangle {
            height: 1  // 分隔线高度
            width: parent.width  // 分隔线宽度
            color: "gray"  // 分隔线颜色
            Layout.fillWidth: true
        }
        // 聊天区域
        Rectangle {
            width: parent.width
            height: parent.height - 120 // 减去顶部工具栏的高度

            Column {
                anchors.fill: parent

                // 聊天消息显示区
                Rectangle {
                    id: messageDisplay
                    width: parent.width
                    height: parent.height - 100
                    color: "#ffffff"

                    ListView {
                        anchors.fill: parent
                        spacing:5
                        model: ListModel {
                            id: messageModel
                            ListElement { sender: "对方"; message: "你好！"; isMe: false }
                            ListElement { sender: "我"; message: "你好！有什么事吗？"; isMe: true }
                            ListElement { sender: "对方"; message: "我想和你讨论一下项目。"; isMe: false }
                        }
                        delegate: Rectangle {
                            width: parent.width/2
                            height: messageText.implicitHeight + 20
                            color: isMe ? "#dcf8c6" : "lightblue"
                            radius: 5

                            anchors.right: isMe ? parent.right : undefined
                            anchors.left: isMe ? undefined : parent.left

                            Text {
                                id: messageText
                                text: message
                                anchors.centerIn: parent
                                width: parent.width - 20
                                wrapMode: Text.Wrap
                                color: isMe ? "black" : "black"
                            }

                            Label{
                                id: timeText
                                text: isMe ? (Qt.formatDateTime(new Date(), "hh:mm")+"  "+startWindow.globalNicknametext):Qt.formatDateTime(new Date(), "hh:mm")+" "+nameMessage.text
                                // text: Qt.formatDateTime(new Date(), "hh:mm")+"  "+startWindow.globalNicknametext
                                color: "gray"
                                font.pixelSize: 10
                                horizontalAlignment: isMe ?Text.AlignRight:Text.AlignLeft
                            }
                            // Text{
                            //     id:messagesender
                            //     text:"lll"
                            //     font.pixelSize: 10
                            //     height: timeText.height
                            //     anchors.bottom: messageText.bottom
                            //     anchors.left: timeText.right

                            // }
                        }
                    }
                }

                // 消息输入区
                Rectangle {
                    width: parent.width
                    height: 143
                    color: "white"


                    ToolBar{
                        id:ll
                        RowLayout {
                            anchors.fill: parent
                            spacing: 2

                            // 表情按钮
                            Button {
                                text: "😊 "
                                onClicked: {
                                    // 实现表情选择的逻辑
                                    emojiPopup.open()
                                    console.log("表情");

                                }
                                background: Rectangle {
                                    color: "transparent"  // 设置背景颜色为透明
                                    border.color: "transparent"  // 设置边框颜色为透明
                                    border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为蓝色

                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            // 导入 EmojiPopup
                            EmojiPopup {
                                id: emojiPopup
                                onEmojiSelected: {
                                    messageInput.text += emoji  // 将选中的表情添加到输入框
                                }

                            }




                            // 更多按钮
                            Button {
                                text: "+"
                                onClicked: {
                                    // 实现更多的逻辑
                                    console.log("更多");
                                }
                                background: Rectangle {
                                    color: "transparent"  // 设置背景颜色为透明
                                    border.color: "transparent"  // 设置边框颜色为透明
                                    border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为蓝色
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                    }
                    // 输入框
                    TextField {
                        id: messageInput
                        anchors.fill: parent
                        anchors.top:ll.bottom
                        anchors.topMargin: 30
                        anchors.bottom: parent.bottom
                        // anchors.leftMargin: 10
                        // anchors.rightMargin: 10
                        // font.family: "Microsoft YaHei"
                        placeholderText: "输入消息..."
                        placeholderTextColor: "grey"
                        width:40
                    }

                    // 发送按钮
                    Button {
                        id:sendbutton
                        text: "发送"
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.bottom: messageInput.bottom
                        anchors.bottomMargin: 10
                        enabled: messageInput.text.length > 0  // 根据输入框内容启用或禁用按钮
                        onClicked: {
                            console.log("发送消息: " + messageInput.text)
                            EchooClient.SendMessage("0721",messageInput.text);
                            messageModel.append({ sender: "我", message: messageInput.text, isMe: true })
                            messageInput.text = ""

                        }
                    }
                    Button {
                        text: "关闭"
                        anchors.right: sendbutton.left
                        anchors.rightMargin: 10
                        anchors.bottom: messageInput.bottom
                        anchors.bottomMargin: 10
                        onClicked: {
                            chatwidget.visible = false
                            console.log("关闭聊天窗口" )

                        }
                    }
                }
            }
        }
    }
}
