//主页
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    property alias rootWindow: rootWindow
    property alias titleBar: titleBar
    property alias toolBars: toolBars
    property var message: null;
    property var friend: null;
    property var group: null;

    id: rootWindow
    width: toolBars.width + titleBar.Layout.preferredWidth
    height: toolBars.height
    visible: true

    RowLayout {
        anchors.fill: parent

        ToolBars {
            id: toolBars
            message.onClicked: {
                messagePage.visible = true;
                friendPage.visible = false;
                groupPage.visible = false;
            }
            friend.onClicked: {
                friendPage.visible = true;
                messagePage.visible = false;
                groupPage.visible = false;
            }
            group.onClicked: {
                groupPage.visible = true;
                messagePage.visible = false;
                friendPage.visible = false;
            }
        }

        Rectangle {
            id: right
            Layout.fillWidth: true
            Layout.fillHeight: true


            ColumnLayout {
                anchors.fill: parent

                MainpagetitleBar {
                    id: titleBar
                    Layout.preferredWidth: 600
                    minimizeButton.onClicked: rootWindow.showMinimized()
                }

                Rectangle {
                    Layout.preferredWidth: titleBar.width
                    Layout.fillHeight: true
                    color: "transparent"  // 透明背景

                    Messagetotal {
                        id: messagePage
                        anchors.fill: parent
                        visible: true

                        Connections {
                            target: EchooClient
                            function onReceivedFriendResponse(user, result) {
                                console.log("result： "+result)
                                if(result){
                                    var messages = EchooClient.GetMessageList(user.account)
                                    console.log("添加的好友： "+user.account)
                                    messagePage.messagelistModel.append({picture1: "",name1: user.nickname, lastMessage1: messages[messages.length-1].content, time1: messages[messages.length-1].timestamp,
                                                                            unreadCount1: 0,_isGroup: 0, account1: user.account})
                                }
                            }

                        }
                    }


                    // 好友页面
                    Friendtotal {
                        id: friendPage
                        anchors.fill: parent
                        visible: false

                    }

                    // 群组页面
                    Grouptotal {
                        id: groupPage
                        anchors.fill: parent
                        visible: false
                    }
                }

            }
        }
    }
}

