// EmojiPopup.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: emojiPopup
    width: 300
    height: 200
    x:10
    y:-200
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    // 表情网格布局
    GridLayout {
        anchors.fill: parent
        columns: 5
        rowSpacing: 5
        columnSpacing: 5

        // 示例表情（可以替换为实际表情）
        Repeater {
            model: ["😊", "😂",  "😎", "🤔", "😴", "😇", "🤗", "😋", "🤩", "😘", "😍", "😘", "😚", "😙",  "😋", "😛", "😜"]

            Button {
                text: modelData
                width: 40
                height: 40
                onClicked: {
                    emojiPopup.emojiSelected(modelData)  // 触发自定义信号
                    emojiPopup.close()  // 关闭表情选择框
                }
                background: Rectangle {
                    color: "transparent"
                    border.color: "transparent"
                }
                contentItem: Text {
                    text: parent.text
                    color: parent.hovered ? "red" : "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                }
            }
        }
    }

    // 自定义信号：当表情被选中时触发
    signal emojiSelected(string emoji)
}
