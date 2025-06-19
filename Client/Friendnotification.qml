import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FrameLessWindow {
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
                color: mouseArea.containsMouse ? "#e0e0e0" : "transparent" // 悬停时灰色，否则交替色

                // 添加鼠标区域
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true // 启用悬停检测
                    cursorShape: Qt.PointingHandCursor // 悬停时显示手型指针
                    onClicked: {
                        // 点击项的处理逻辑（可选）
                        console.log("Clicked:", model.name1)
                    }
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
                            // id:ffriendname
                            text: model.name1
                            font.bold: true
                        }
                        Label {
                            text: model.aaction1
                            color: "#666"
                        }
                    }
                    Label{
                        id:friendaccount
                        text:model.account
                        visible: false
                    }

                    RowLayout{
                        Layout.alignment: Qt.AlignRight
                        spacing:0
                        Button{
                            id: accepet
                            text:"同意"
                            onClicked: {
                                // EchooClient.AddFriend(friendaccount);
                                enabled = false
                                reject.enabled = false
                            }
                        }
                        Button{
                            id: reject
                            text: "拒绝"
                            onClicked: {
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
        ListElement{
            image1: ""
            name1: "111"
            aaction1: "222"
            account:"333"
        }
        ListElement{
            image1: ""
            name1: "111"
            aaction1: "222"
            account:"333"
        }
    }


}

