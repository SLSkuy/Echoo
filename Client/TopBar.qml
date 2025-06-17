import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

//titlebar
Rectangle {
    property alias text11: widgettext

        id: titleBar
        width: parent.width
        height: 40
        color: "transparent"  // 标题栏背景颜色

        RowLayout {
            anchors.fill: parent
            // spacing: 10

            // 窗口标题
            Text {
                id:widgettext
                text: "name"
                color: "black"
                font.pixelSize: 14
                Layout.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
            }

            Item {
                Layout.fillWidth: true  // 占位符，将按钮推到右侧
            }

            // 最小化按钮
            Button {
                id: minimizeButton
                text: "—"

                width: 25
                Layout.preferredHeight: 20
                onClicked: chatwidget.showMinimized()
                background: Rectangle {
                       color: "transparent"  // 设置背景颜色为透明
                       border.color: "transparent"  // 设置边框颜色为透明
                       border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                   }
                contentItem: Text {
                    text: parent.text
                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            // 最大化/还原按钮
            Button {
                id: maximizeButton
                text: chatwidget.visibility === Window.Maximized ? "r" : "+"
                width: 25
                Layout.preferredHeight: 20
                onClicked: {
                    if (chatwidget.visibility === Window.Maximized) {
                        chatwidget.showNormal()
                    } else {
                        chatwidget.showMaximized()
                    }
                }
                background: Rectangle {
                       color: "transparent"  // 设置背景颜色为透明
                       border.color: "transparent"  // 设置边框颜色为透明
                       border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                   }
                contentItem: Text {
                    text: parent.text
                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            // 关闭按钮
            Button {
                id: closeButton
                text: "x"
                width: 25
                Layout.preferredHeight: 20
                onClicked: chatwidget.close()
                background: Rectangle {
                       color: "transparent"  // 设置背景颜色为透明
                       border.color: "transparent"  // 设置边框颜色为透明
                       border.width: 2  // 设置边框宽度（可选，透明边框时宽度不影响视觉效果）
                   }
                contentItem: Text {
                    text: parent.text
                    color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
