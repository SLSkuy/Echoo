import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    id: rootWindow
    width: 600
    height: 700
    visible: true
    color: "#FFFFFF"

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: 0

        // 左侧工具栏
        ToolBars {
            id: toolBars
            Layout.preferredWidth: 70
            Layout.fillHeight: true
            message.onClicked: {messagePage.visible = true; friendPage.visible = false;}
            friend.onClicked: {friendPage.visible = true; messagePage.visible = false;}
        }

        // 右侧区域
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                // 标题栏
                MainpagetitleBar {
                    id: mainPage
                    Layout.fillWidth: true
                    Layout.preferredHeight: 70
                    minimizeButton.onClicked: rootWindow.showMinimized()
                }

                // 内容区域
                Rectangle {
                    id: contentArea
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 5
                    color: "#F5F5F5"

                    Messagetotal {
                        id: messagePage
                        anchors.fill: parent
                        visible: true
                        // color:"red"
                    }

                    Friendtotal {
                        id: friendPage
                        anchors.fill: parent
                        // notificationwidth:contentArea.width
                        visible: false
                        // color:"red"
                    }
                }
            }
        }
    }
}
