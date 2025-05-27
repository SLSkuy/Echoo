// written by SL-Skuy
// 登录界面示例

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow{
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
        property point mouseOffset: Qt.point(0,0)

        onPressed:function(mouse) {
            mouseOffset.x = mouse.x
            mouseOffset.y = mouse.y
            cursorShape = Qt.ClosedHandCursor
        }

        onReleased:{
            cursorShape = Qt.ArrowCursor
        }

        onPositionChanged:function(mouse) {
            if(mouse.buttons & Qt.LeftButton)
            {
                window.x += mouse.x - mouseOffset.x
                window.y += mouse.y - mouseOffset.y
            }
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
        columns: 2
        rowSpacing: 5
        columnSpacing: 10

        Label { text: "账号:" }
        TextField { Layout.fillWidth: true }

        Label { text: "密码:" }
        TextField {
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        Item { Layout.columnSpan: 2; height: 10 } // 空隙
        Button {
            text: "登录"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
