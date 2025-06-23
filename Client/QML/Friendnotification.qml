//好友通知

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "../listmodels.js" as GlobalModels

FrameLessWindow {
    property alias friendlistmodelnotification: listModel
    property alias friendnotification: f_notification
    property bool select: false
    signal selectStatusChanged(bool selected)

    property var friendsModel: friendstotal.friendlistmodel

    id:f_notification
    visible: true
    width: 500
    height: 600


    // 主布局
    Column{
        id:column
        anchors.fill: parent
        spacing: 2

        Rectangle {
            Layout.topMargin: 5
            Layout.alignment: Qt.AlignTop
            id: titleBar
            width: parent.width
            height: 40
            color: "transparent"  // 标题栏背景颜色

            RowLayout {
                anchors.fill: parent
                // spacing: 10

                // 窗口标题
                Text {
                    id:text
                    text:"好友通知"
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
                    onClicked: f_notification.showMinimized()
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
                    text: f_notification.visibility === Window.Maximized ? "r" : "+"
                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: {
                        if (f_notification.visibility === Window.Maximized) {
                            f_notification.showNormal()
                        } else {
                            f_notification.showMaximized()
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
                    onClicked: f_notification.close()
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
            }
        }

        Text{
            id: bin
            text: "🗑️"
            anchors.right: parent.right
            anchors.rightMargin: 8
            font.pixelSize: 18
            // color: hovered ? "red" : "transparent"
            TapHandler{
                onTapped:{
                    listModel.clear();
                }
            }
        }

        ListView {
            id: notification
            width: parent.width
            height: parent.height-bin.height-titleBar.height
            model: listModel
            spacing: 5 // 项间距

            delegate: Rectangle {
                width: notification.width
                height: 60

                color: hoverHandler.hovered ? "#E6E6E6" : "transparent" // 悬停变灰

                //悬停变灰
                HoverHandler {
                    id: hoverHandler
                }

                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    Image {
                        Layout.preferredWidth: 40
                        Layout.preferredHeight: 40
                        source: model.image1
                    }

                    ColumnLayout {
                        Layout.alignment: Qt.AlignLeft
                        Label {
                            id:name
                            // id:ffriendname
                            text: model.name1
                            font.bold: true
                        }
                        Label {
                            id:aaction
                            text: model.aaction1
                            color: "#666"
                        }
                    }
                    Label{
                        id:friendaccount
                        text:model.account1
                        visible: false
                    }

                    RowLayout{
                        Layout.alignment: Qt.AlignRight
                        spacing:0
                        Button{
                            id: accepet
                            text:"同意"
                            onClicked: {
                                select = true;
                                selectStatusChanged(select); // 发射信号
                                EchooClient.addFriendResponse(friendaccount.text,select);
                                enabled = false
                                reject.enabled = false

                                if(select){
                                    console.log(select)
                                    var netizen = EchooClient.getNetizen(friendaccount.text)
                                    var message = EchooClient.getMessageList(netizen.account)
<<<<<<< HEAD
                                    EchooClient.acceptFriendRequest(netizen,message)
                                    // GlobalModels.addFriend(netizen)

                                    // GlobalModels.addMessagelist(netizen, message)
=======
                                    // GlobalModels.friendlistModelinit(friendsModel);
                                    GlobalModels.addFriend(netizen)
                                    // GlobalModels.friendsModel.append({
                                    //                 headPortrait: netizen.avatar,
                                    //                 name: netizen.nickname,
                                    //                 account: netizen.account
                                    //             });
                                    GlobalModels.addMessagelist(netizen, message)
>>>>>>> 4a934803e048bfc87adcc1463a9e4fb96df07f84
                                }
                            }
                        }
                        Button{
                            id: reject
                            text: "拒绝"
                            onClicked: {
                                select = false
                                EchooClient.addFriendResponse(friendaccount.text,select);
                                enabled = false
                                accepet.enabled = false
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel{
        id: listModel

    }

    Connections {
        target: EchooClient
        function onReceivedFriendRequest(addfriendnotification) {
            console.log("aaa")
            listModel.append({image1:addfriendnotification.avatar, name1:addfriendnotification.nickname, aaction1: "请求添加你为好友", account1:addfriendnotification.account})
        }
    }


}

