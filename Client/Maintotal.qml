import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    property alias rootWindow: rootWindow
    property alias titleBar: titleBar
    property alias toolBars: toolBars

    id: rootWindow
    width: toolBars.width + titleBar.Layout.preferredWidth
    height: toolBars.height
    visible: true

    // 存储不同状态的组件
    property var stateComponents: ({})

    RowLayout {
        anchors.fill: parent

        ToolBars {
            id: toolBars
            message.onClicked: right.state = "message"
            friend.onClicked: right.state = "friend"
            group.onClicked: right.state = "group"
        }

        Rectangle {
            id: right
            Layout.fillWidth: true
            Layout.fillHeight: true

            state: "message"

            ColumnLayout {
                anchors.fill: parent

                MainpagetitleBar {
                    id: titleBar
                    Layout.preferredWidth: 600
                    minimizeButton.onClicked: rootWindow.showMinimized()
                }

                // 使用StackLayout来管理不同状态的视图
                StackLayout {
                    id: viewStack
                    width: titleBar.width
                    height: rootWindow.height - titleBar.height
                    Layout.fillHeight: true

                    currentIndex: {
                        switch(right.state) {
                        case "message": return 0
                        case "friend": return 1
                        case "group": return 2
                        default: return 0
                        }
                    }

                    // 消息页面
                    Loader {
                        id: messageLoader
                        active: false
                        sourceComponent: Component {
                            id: messageComponent
                            Messagetotal {}
                        }
                        onLoaded: rootWindow.stateComponents["message"] = item
                    }

                    // 好友页面
                    Loader {
                        id: friendLoader
                        active: false
                        sourceComponent: Component {
                            id: friendComponent
                            Friendtotal {}
                        }
                        onLoaded: rootWindow.stateComponents["friend"] = item
                    }

                    // 群组页面
                    Loader {
                        id: groupLoader
                        active: false
                        sourceComponent: Component {
                            id: groupComponent
                            Grouptotal {}
                        }
                        onLoaded: rootWindow.stateComponents["group"] = item
                    }
                }
            }

            states: [
                State {
                    name: "message"
                    StateChangeScript {
                        script: {
                            if (!rootWindow.stateComponents["message"]) {
                                messageLoader.active = true
                            } else {
                                viewStack.currentIndex = 0
                            }
                        }
                    }
                },
                State {
                    name: "friend"
                    StateChangeScript {
                        script: {
                            if (!rootWindow.stateComponents["friend"]) {
                                friendLoader.active = true
                            } else {
                                viewStack.currentIndex = 1
                            }
                        }
                    }
                },
                State {
                    name: "group"
                    StateChangeScript {
                        script: {
                            if (!rootWindow.stateComponents["group"]) {
                                groupLoader.active = true
                            } else {
                                viewStack.currentIndex = 2
                            }
                        }
                    }
                }
            ]
        }
    }
}
