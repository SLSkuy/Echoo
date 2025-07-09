// written by SL_Skuy
// 注册界面模块

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item{
    implicitHeight: grid.implicitHeight
    implicitWidth: grid.implicitWidth

    Rectangle {
        id: successIndicator
        color: "gray"
        width: 200
        height: 70
        anchors.centerIn: parent
        visible: false
        radius: 10
        z: 10
        Text {
            text: "注册成功!"
            anchors.centerIn: parent
            color: "white"
        }
    }

    Timer {
        id: successTimer
        interval: 3000 // 3秒
        onTriggered: {
            successIndicator.visible = false;
        }
    }

    Rectangle {
        id: failure
        anchors.centerIn: parent
        width: 200
        height: 70
        color: "lightgray"
        z:10
        visible: false
        ColumnLayout{
            anchors.fill: parent
            Label {
                text: "注册失败: 该账号已被注册!"
                Layout.preferredWidth: parent.width
                color: "red"
            }
            Button{
                id:ok
                text:"OK"
                onClicked: {
                    failure.visible = false
                }
            }
        }

    }

    GridLayout {
        id:grid
        anchors.fill: parent
        columns: 1
        columnSpacing: 10

        Image{
            source: "qrc:/resources/LoginImage.png"
            Layout.preferredHeight: 80
            Layout.preferredWidth: 80
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 20
        }

        TextField{
            id: nickNameLine

            // 输入框中文本设置
            placeholderText: "输入Echoo名称"
            placeholderTextColor: "gray"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            // 大小设置
            implicitWidth: 250
            implicitHeight: 40

            background: Rectangle{
                border.color: nickNameLine.focus ? "#21be2b" : "lightgray"
                color: nickNameLine.focus ? "lightgray" : "transparent"
            }

            onTextChanged: regButton.enabled = (accountLine.text.length > 0
                                                && passwordLine.text.length > 0 && nickNameLine.text.length > 0)
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

            onTextChanged: regButton.enabled = (accountLine.text.length > 0
                                                && passwordLine.text.length > 0 && nickNameLine.text.length > 0)
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

            onTextChanged: regButton.enabled = (accountLine.text.length > 0
                                                && passwordLine.text.length > 0 && nickNameLine.text.length > 0)

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
            id: regButton

            enabled: false
            text: "注册"

            // 与accountLine长度和宽度相同
            implicitHeight: accountLine.implicitHeight
            implicitWidth: accountLine.implicitWidth
            Layout.topMargin: 50

            background: Rectangle{
                color: regButton.enabled === false ? "skyblue" : "#1E90FF"
                border.color: "transparent"
            }

            Connections{
                target: EchooClient
                function onRegisterSuccess(result){
                    if (result) {
                        successIndicator.visible = true;
                        successTimer.start();
                    } else {
                        failure.visible = true;
                    }
                }
            }

            // 测试输出
            onClicked: {
                console.log("注册信息: " + " " + nickNameLine.text + " " + accountLine.text + " " + passwordLine.text)
                EchooClient.reg(nickNameLine.text,accountLine.text,passwordLine.text)
            }
        }
    }
}
