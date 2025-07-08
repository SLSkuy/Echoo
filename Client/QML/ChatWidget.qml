import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs
import "../listmodels.js" as GlobalModels

FrameLessWindow {
    property alias topBar: topbar
    property string receiver
    property string account
    property alias chatwidget: chatwidget
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
                color: "white"
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
                        delay: 500
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
                        color: "white"
                        border.color: "white"
                        border.width: 2
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
                        console.log("删除好友");

                        // console.log(messageItem[1].account1)i < mainWindow.messageListModel.count
                        for (var i = 0; i < messagetotal.messagelistModel.count; i++) {
                            var item = messagetotal.messagelistModel.get(i);
                            if (item.account === chatwidget.account) {
                                messagetotal.messagelistModel.remove(i);
                                break;
                            }
                        }

                        var myselfAccount = EchooClient.getThisInfo().account;
                        var netizen = EchooClient.getNetizen(account)
                        // EchooClient.removeFriendList(netizen,myselfAccount)
                        // EchooClient.removeFriendsSignals(account);
                        EchooClient.removeFriend(account);
                        chatwidget.close();
                        }

                    background: Rectangle {
                        color: "white"
                        border.color: "white"
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

        Rectangle {
            height: 1  // 分隔线高度
            width: parent.width  // 分隔线宽度
            color: "gray"  // 分隔线颜色
            Layout.fillWidth: true
        }
        // 聊天区域
        Rectangle {
            width: parent.width
            height: parent.height - 120

            TapHandler{
                onTapped:{
                    EchooClient.clearunreadcount(account);
                }
            }

            Column {
                anchors.fill: parent

                // 聊天消息显示区
                Rectangle {
                    id: messageDisplay
                    width: parent.width
                    height: parent.height - 100
                    color: "#ffffff"

                    MessageWidget{
                        id: messageListView
                        anchors.fill: parent
                        // myNickname: EchooClient.getThisInfo().nickname;
                        receiverName:receiver;
                        model: ListModel {
                            id: messageModel
                        }

                        Component.onCompleted: {
                        // 传入账号获取消息列表和昵称
                            var messageList = EchooClient.getMessageList(account);
                            var user = EchooClient.getThisInfo();
                            myNickname=user.nickname;
                            for (var i = 0; i < messageList.length; i++) {
                                // 示例处理
                                messageModel.append({
                                    picture:"",
                                    message: messageList[i].content,
                                    isMe: !(messageList[i].sender.account === account)})
                                }
                            }
                        }
                    }

                // 消息输入区
                Rectangle {
                    width: parent.width
                    height: 143
                    color: "white"

                    TapHandler{
                        onTapped:{
                            EchooClient.clearunreadcount(account);
                        }
                    }


                    ToolBar{
                        id:textfieldtoolbar
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
                                    color: "transparent"
                                    border.color: "transparent"
                                    border.width: 2
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
                                    fileDialog.open()
                                }
                                background: Rectangle {
                                    color: "transparent"
                                    border.color: "transparent"
                                    border.width: 2
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为蓝色
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                FileDialog {
                                    id: fileDialog
                                    title: "Select an Image"
                                    nameFilters: ["Image files (*.png *.jpg *.jpeg)"] // 过滤图片文件
                                    onAccepted: {
                                        var filePath = fileDialog.selectedFile.toString();
                                        // EchooClient.triggerImage(account,filePath);
                                        EchooClient.sendImage(account,filePath);
                                        messageModel.append({ picture:filePath, isMe: true })
                                    }
                                }
                            }
                        }
                    }
                    // 输入框
                    TextField {
                        id: messageInput
                        anchors.fill: parent
                        anchors.top:textfieldtoolbar.bottom
                        anchors.topMargin: 30
                        anchors.bottom: parent.bottom
                        placeholderText: "输入消息..."
                        placeholderTextColor: "grey"
                        width:40
                        TapHandler{
                            onTapped:{
                                EchooClient.clearunreadcount(account);
                            }
                        }
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
                            EchooClient.triggerMessage(account,messageInput.text);
                            messageModel.append({ sender: "我", message: messageInput.text, isMe: true })
                            messageInput.text = ""
                            EchooClient.clearunreadcount(account);

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
                            EchooClient.clearunreadcount(account);

                        }
                    }
                }
            }
        }

    }

    // 接受消息
    Connections {
        target: EchooClient
        function onMessageReceived(msg) {
            messageModel.append({message: msg.content,isMe: !(msg.sender.account === account)})
            console.log("message");


        }
        function onImgReceived(msgg){
            messageModel.append({picture: msgg.content,isMe: !(msgg.sender.account === account)})
            console.log("image")
        }
    }

    // signal removeFriendRequested(string account)
    // function removeFriend(){
    //       for (var j = 0; j < friendstotal.friendlistmodel.count; j++) {
    //           var item1 = friendstotal.friendlistmodel.get(j);
    //           if (item1.account === chatwidget.account) {
    //               friendstotal.friendlistmodel.remove(j);
    //               console.log("delete")
    //               break;
    //           }
    //       }
    //       console.log("out")
    //   }


    Component.onCompleted: {
        EchooClient.clearunreadcount(account);
    }
}
