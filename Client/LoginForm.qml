// writen by SL_Skuy
// 登录界面模块

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GridLayout {
    columns: 1
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
        implicitWidth: 250
        implicitHeight: 40

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

        Button{
            id: hidenButton
            text: "👀"

            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: parent.height * 0.15

            implicitHeight: parent.implicitHeight * 0.7
            implicitWidth: parent.implicitHeight * 0.7

            onClicked: passwordLine.echoMode === TextInput.Password
                        ? passwordLine.echoMode = TextInput.Normal
                        : passwordLine.echoMode = TextInput.Password
        }
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
            EchooClient.Login(accountLine.text,passwordLine.text)
        }
    }
}
