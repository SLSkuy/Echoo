import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    id: rootWindow
    width: toolBars.width + infoArea.implicitWidth
    height: toolBars.height
    visible: true

    RowLayout
    {
        anchors.fill: parent
        spacing: 0
        // 左侧工具栏
        ToolBars {
            id: toolBars
            message.onClicked: {messagePage.visible = true;friendPage.visible = false;}
            friend.onClicked: {friendPage.visible = true;messagePage.visible = false;}
        }

        // 右侧区域
        ColumnLayout {
            id: infoArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // 搜索栏与标题栏
            MainpagetitleBar {
                id: mainPage
                Layout.preferredWidth: 550
                minimizeButton.onClicked: rootWindow.showMinimized()
            }

            // 消息栏区域
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rightMargin: 5
                Layout.leftMargin: 5
                Layout.bottomMargin: 5

                Messagetotal {
                    id: messagePage
                    anchors.fill: parent
                    visible: true
                }

                // 好友页面
                Friendtotal {
                    id: friendPage
                    anchors.fill: parent
                    visible: false
                }
            }
        }
    }
}

