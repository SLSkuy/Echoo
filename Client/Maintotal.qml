//总的主页面 可以选择展示不同的页面

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    property  alias rootWindow: rootWindow
    property  alias titleBar : titleBar
    property  alias toolBars : toolBars

    id: rootWindow
    width: toolBars.width + titleBar.Layout.preferredWidth
    height: toolBars.height
    visible: true
    flags: Qt.FramelessWindowHint


    RowLayout {
        anchors.fill: parent

        ToolBars {
            id: toolBars
            message.onClicked: {
                right.state = "message"
            }
            friend.onClicked:{
                right.state= "friend"
            }
            group.onClicked:{
                right.state= "group"
            }
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
                    Layout.preferredWidth:600
                    minimizeButton.onClicked: rootWindow.showMinimized()
                }

                Loader {
                        id: delegateLoader
                        width: titleBar.width
                        height:rootWindow.height - titleBar.heigh
                        Layout.fillHeight: true
                }
            }
            states: [
                State{
                    name:"message"
                    PropertyChanges {
                        target: delegateLoader
                        source:"Messagetotal.qml"
                    }
                },
                State{
                    name:"friend"
                    PropertyChanges {
                        target: delegateLoader
                        source:"Friendtotal.qml"
                    }
                },
                State {
                    name: "group"
                    PropertyChanges {
                        target: delegateLoader
                        source: "Grouptotal.qml"
                    }
                }
            ]
        }
    }
}
