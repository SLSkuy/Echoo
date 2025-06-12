// written by SL_Skuy
// 标题栏模块

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    spacing: 0

    Button{
        // 设置按钮
        id: optionButton
        text: "⚙"
        // icon.source: "image.png" 后期替换

        implicitHeight: 35
        implicitWidth: 35

        background: Rectangle{
            color: optionButton.hovered ? "red" : "transparent"
            border.color: "transparent"
        }
    }

    Button{
        // 退出按钮
        id: closeButton
        text: "×"
        // icon.source: "image.png" 后期替换

        implicitHeight: 35
        implicitWidth: 35

        onClicked: Qt.quit()

        background: Rectangle{
            color: closeButton.hovered ? "red" : "transparent"
            border.color: "transparent"
        }
    }
}
