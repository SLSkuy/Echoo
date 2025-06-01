// written by SL-Skuy
// Echoo登录界面

import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window{
    id: startWindow
    height: 450
    width: 320
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Window

    Rectangle{
        id: rootContainer
        anchors.fill: parent
        state: "loginState"

        // 实现全局拖拽功能
        MouseArea{
            id: dragArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.ArrowCursor

            onPressed:function() {
                cursorShape = Qt.ClosedHandCursor
                startWindow.startSystemMove()
            }

            onReleased:{
                cursorShape = Qt.ArrowCursor
            }
        }

        TitleBar{
            anchors.right: parent.right
            anchors.top: parent.top
        }

        LoginForm{
            id: loginWindow
            anchors.centerIn: parent
        }

        RegForm{
            id: regWindow
            opacity: 0
            anchors.centerIn: parent
        }

        Button{
            id: stateSwitchButton
            text: rootContainer.state === "loginState" ? "注册" : "登录"
            onClicked:
            {
                rootContainer.state = (rootContainer.state === "loginState") ? "regState" : "loginState"
            }
        }

        states: [
            State {
                name: "loginState"
                PropertyChanges {
                    loginWindow.enabled: true
                    regWindow.enabled: false
                    loginWindow.opacity: 1
                    regWindow.opacity: 0
                }
            },
            State {
                name: "regState"
                PropertyChanges {
                    loginWindow.enabled: false
                    regWindow.enabled: true
                    loginWindow.opacity: 0
                    regWindow.opacity: 1
                }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation{
                    properties: "opacity"
                    easing.type: Easing.InOutQuad
                    duration: 500
                }
            }
        ]
    }
}
