// written by SL-Skuy
// Echoo登录界面

import QtQuick
import QtQuick.Window
import QtQuick.Controls

FrameLessWindow{
    property string globalAccountId: ""
    property string globalNicknametext: ""
    id: startWindow

    Rectangle{
        id: rootContainer
        anchors.fill: parent
        state: "loginState"

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

        Connections {
            target: EchooClient
            function onLoginSuccess(result) {
                var userWindow = Qt.createComponent("Maintotal.qml")
                if(userWindow.status === Component.Ready && result) {
                    var user = userWindow.createObject()
                    user.show()
                    startWindow.close()
                }
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
