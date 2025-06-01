// written by SL-Skuy
// Echoo登录界面

import QtQuick
import QtQuick.Window

Window{
    id: startWindow
    height: 450
    width: 320
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Window

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
        anchors.centerIn: parent
    }
}
