//好友通知

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FrameLessWindow {
    property alias friendlistmodelnotification: listModel
    property alias friendnotification: chatwidget
    property bool select: false
    signal selectStatusChanged(bool selected)

    id:chatwidget
    visible: true
    width: 500
    height: 600


    // 主布局
    Column{
        id:column
        anchors.fill: parent
        spacing: 2

        TopBar{
            id:topbar
            Layout.alignment: Qt.AlignTop
            Layout.topMargin: 5
            text11.text:"好友通知"
            text11.font.pixelSize: 18
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
            height: parent.height-bin.height-topbar.height
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
                                // console.log(friendaccount)
                                EchooClient.AddFriendResponse(friendaccount.text,select);
                                enabled = false
                                reject.enabled = false
                            }
                        }
                        Button{
                            id: reject
                            text: "拒绝"
                            onClicked: {
                                select = false
                                EchooClient.AddFriendResponse(friendaccount.text,select);
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
            listModel.append({image1:"", name1:addfriendnotification.nickname, aaction1: "请求添加你为好友", account1:addfriendnotification.account})
        }
    }


}

