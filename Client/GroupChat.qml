import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Window {
    id:chatwidget
    visible: true
    width: 800
    height: 600
    title: "QQ聊天窗口"
    flags: Qt.FramelessWindowHint | Qt.Window


    //拖动全局窗口
    MouseArea{
        id: dragArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor

        onPressed:function() {
            cursorShape = Qt.ClosedHandCursor
            chatwidget.startSystemMove()
        }

        onReleased:{
            cursorShape = Qt.ArrowCursor
        }
    }


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
                    onClicked: {
                        // 实现发起群聊的逻辑
                        console.log("发起群聊");
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



                // 更多按钮
                Button {
                    // text:"more"
                    text: "···"
                    onClicked: {
                        // 实现更多的逻辑
                        console.log("更多");
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

                RowLayout{
                    height: parent.height - 100
                    width: parent.width

                // 聊天消息显示区
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        id: messageDisplay
                        width: parent.width
                        height: parent.height
                        color: "#ffffff"

                        ListView {
                            anchors.fill: parent
                            model: 3 // 示例消息数量
                            delegate: Item {
                                width: messageDisplay.width
                                height: 30
                                Text {
                                    text: "消息 " + (index + 1)
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                    //设置分割线
                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        width: 1
                        height: parent.height
                        color: "#E6E6E6"
                        anchors.right: members.left
                        // Layout.rightMargin: 15
                        anchors.rightMargin: 15

                    }
                    //显示群成员
                    Rectangle{
                        id:members
                        Layout.alignment: Qt.AlignTop
                        ColumnLayout{
                            anchors.fill: parent
                            Label{
                                text: "群聊成员"
                                // anchors.topMargin: 100
                                font.pixelSize: 14
                                color: "black"
                                width: parent.width
                                height: 30
                            }
                            Rectangle{
                                height: 400
                                // Layout.fillHeight: true
                                width: 200
                            ListView{
                                id:member
                                model: memberlist

                                // Layout.fillHeight: true
                                height: parent.height
                                width: parent.width
                                delegate: Rectangle{
                                    height: 40
                                    width: member.width
                                    RowLayout{
                                    anchors.fill: parent
                                    Image{
                                        source: model.image1
                                        Layout.preferredWidth: 15
                                        Layout.preferredHeight: 15
                                        // TapHandler{
                                        //     onTapped: console.log("aaa")
                                        // }
                                    }
                                    Text {
                                        height: 20
                                        // width:parent.width
                                        Layout.fillWidth: true
                                        text: model.name1
                                        color: "black"
                                    }
                                }
                                }
                            }
                            }
                        }
                        ListModel{
                            id: memberlist
                            ListElement{image1:""
                                        name1:"111"}
                            ListElement{image1:""
                                        name1:"222"}
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
                                    console.log("表情");
                                    // emojiPopup.open()
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




                            // 更多按钮
                            Button {
                                text: "⊕"
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
                            EchooClient.SendPrivateMessage(messageInput.text,"123");
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
