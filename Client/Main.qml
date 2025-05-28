// written by SL-Skuy
// 登录界面示例

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Window{
    id: window
    height: 450
    width: 320
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Window
    MouseArea{
        // 实现全局拖拽功能
        id: dragArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor

        onPressed:function(mouse) {
            cursorShape = Qt.ClosedHandCursor
            window.startSystemMove()
        }

        onReleased:{
            cursorShape = Qt.ArrowCursor
        }
    }

    Button{
        // 退出按钮
        id: closeButton
        text: "×"
        // icon.source: "image.png" 后期替换
        height: 35
        width: 35
        anchors.right: parent.right
        anchors.top: parent.top

        onClicked: Qt.quit()

        background: Rectangle{
            color: closeButton.hovered ? "red" : "transparent"
            border.color: "transparent"
        }
    }

    Button{
        // 设置按钮
        id: optionButton
        text: "⚙"
        // icon.source: "image.png" 后期替换
        height: 35
        width: 35
        anchors.right: closeButton.left

        background: Rectangle{
            color: optionButton.hovered ? "red" : "transparent"
            border.color: "transparent"
        }
    }

    GridLayout {
        anchors.centerIn: parent
        columns: 1
        rowSpacing: 5
        columnSpacing: 10

        Image{
            source: "qrc:/resources/LoginImage.png"
            Layout.preferredHeight: 80
            Layout.preferredWidth: 80
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 20
        }

        TextField {
            id: accountLine

            // 输入框中文本设置
            placeholderText: "输入Echoo号"
            placeholderTextColor: "gray"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            // 大小设置
            implicitWidth: 200
            implicitHeight: 30

            background: Rectangle{
                border.color: accountLine.focus ? "#21be2b" : "lightgray"
                color: accountLine.focus ? "lightgray" : "transparent"
            }

            onTextChanged: loginButton.enabled = (accountLine.text.length > 0 && passwordLine.text.length > 0)
        }

        TextField {
            id: passwordLine

            // 输入框中文本设置
            placeholderText: "输入Echoo密码"
            placeholderTextColor: "gray"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            // 使输入的密码变为 *
            echoMode: TextInput.Password

            // 与accountLine长度和宽度相同
            implicitHeight: accountLine.implicitHeight
            implicitWidth: accountLine.implicitWidth

            background: Rectangle{
                border.color: passwordLine.focus ? "#21be2b" : "lightgray"
                color: passwordLine.focus ? "lightgray" : "transparent"
            }

            onTextChanged: loginButton.enabled = (accountLine.text.length > 0 && passwordLine.text.length > 0)
        }

        Button {
            id: loginButton

            enabled: false
            text: "登录"
            Layout.topMargin: 50    // 单独间距

            // 与accountLine长度和宽度相同
            implicitHeight: accountLine.implicitHeight
            implicitWidth: accountLine.implicitWidth

            background: Rectangle{
                color: loginButton.enabled === false ? "skyblue" : "#1E90FF"
                border.color: "transparent"
            }

            // 测试输出
            onClicked: {
                console.log("账号:", accountLine.text)
                console.log("密码:", passwordLine.text)
            }
        }
    }
}
