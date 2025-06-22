//主页

// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts

// FrameLessWindow {
//     property alias rootWindow: rootWindow
//     property alias titleBar: titleBar
//     property alias toolBars: toolBars

//     id: rootWindow
//     width: toolBars.width + titleBar.Layout.preferredWidth
//     height: toolBars.height
//     visible: true

//     // 存储不同状态的组件
//     property var stateComponents: ({})

//     RowLayout {
//         anchors.fill: parent

//         ToolBars {
//             id: toolBars
//             message.onClicked: right.state = "message"
//             friend.onClicked: right.state = "friend"
//             group.onClicked: right.state = "group"
//         }

//         Rectangle {
//             id: right
//             Layout.fillWidth: true
//             Layout.fillHeight: true

//             state: "message"

//             ColumnLayout {
//                 anchors.fill: parent

//                 MainpagetitleBar {
//                     id: titleBar
//                     Layout.preferredWidth: 600
//                     minimizeButton.onClicked: rootWindow.showMinimized()
//                 }

//                 // 使用StackLayout来管理不同状态的视图
//                 StackLayout {
//                     id: viewStack
//                     width: titleBar.width
//                     height: rootWindow.height - titleBar.height
//                     Layout.fillHeight: true

//                     currentIndex: {
//                         switch(right.state) {
//                         case "message": return 0
//                         case "friend": return 1
//                         case "group": return 2
//                         default: return 0
//                         }
//                     }

//                     // 消息页面
//                     Loader {
//                         id: messageLoader
//                         active: false
//                         sourceComponent: Component {
//                             id: messageComponent
//                             Messagetotal {}
//                         }
//                         onLoaded: rootWindow.stateComponents["message"] = item
//                     }

//                     // 好友页面
//                     Loader {
//                         id: friendLoader
//                         active: false
//                         sourceComponent: Component {
//                             id: friendComponent
//                             Friendtotal {}

//                         }

//                         Connections {
//                             target: EchooClient
//                             // var addfriendnotification = null
//                             function onReceivedFriendRequest(addfriendnotification) {
//                                 console.log("aaa")
//                                 friendlistmodelnotification.append({image1:"", name1:addfriendnotification.nickname, aaction1: "请求添加你为好友", account1:addfriendnotification.account})
//                             }
//                         }
//                         onLoaded: rootWindow.stateComponents["friend"] = item
//                     }

//                     // 群组页面
//                     Loader {
//                         id: groupLoader
//                         active: false
//                         sourceComponent: Component {
//                             id: groupComponent
//                             Grouptotal {}
//                         }
//                         onLoaded: rootWindow.stateComponents["group"] = item
//                     }
//                 }

//             }

//             states: [
//                 State {
//                     name: "message"
//                     StateChangeScript {
//                         script: {
//                             if (!rootWindow.stateComponents["message"]) {
//                                 messageLoader.active = true
//                             } else {
//                                 viewStack.currentIndex = 0
//                             }
//                         }
//                     }
//                 },
//                 State {
//                     name: "friend"
//                     StateChangeScript {
//                         script: {
//                             if (!rootWindow.stateComponents["friend"]) {
//                                 friendLoader.active = true
//                             } else {
//                                 viewStack.currentIndex = 1
//                             }
//                         }
//                     }
//                 },
//                 State {
//                     name: "group"
//                     StateChangeScript {
//                         script: {
//                             if (!rootWindow.stateComponents["group"]) {
//                                 groupLoader.active = true
//                             } else {
//                                 viewStack.currentIndex = 2
//                             }
//                         }
//                     }
//                 }
//             ]
//         }
//     }

// }
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
                            property var addfriend1: null
                            property bool result: friendPage.friendnotification.select
                            function onReceivedFriendResponse(addfriend1, result) {
                                var messages = EchooClient.GetMessageList(addfriend1.account)
                                console.log(addfriend1.account)
                                messagePage.messagelistModel.append({picture1: "",name1: addfriend1.nickname, lastMessage1: messages[messages.length-1].content, time1: messages[messages.length-1].timestamp,
                                                                        unreadCount1: 0,_isGroup: 0, account1: addfriend1.account})
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

