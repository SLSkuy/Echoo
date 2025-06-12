import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    property alias picture: _picture
    property alias name: _name
    property alias lastMessage: _lastMessage
    property alias time: _time
    property alias unreadCount: _unreadCount

    id: root
    // height: 70
    color: mouseArea.containsMouse ? "#E6E6E6" : "transparent"

    RowLayout {
        anchors.fill: parent
        spacing: 10

        // 头像
        Image {
            id: _picture
            Layout.preferredWidth: 50
            Layout.preferredHeight: 50
            Layout.leftMargin: 10
            // fillMode: Image.PreserveAspectFit
        }

        // 消息内容
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 5

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredWidth: 100

                // 联系人名称
                Label {
                    id:_name
                    color: "black"
                    font.pixelSize: 16
                    font.bold: root.unreadCount > 0
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                // 时间
                Label {
                    id: _time
                    text: root.time
                    font.pixelSize: 12
                    color: "darkgrey"
                }
            }

            // 最后一条消息
            Label {
                id:_lastMessage
                font.pixelSize: 14
                color: "grey"
                Layout.fillWidth: true
                elide: Text.ElideRight
            }
        }

        // 未读消息计数
        Rectangle {
            implicitHeight: 20
            implicitWidth: 20
            radius: 10
            color: "red"
            Layout.rightMargin: 10
            Layout.bottomMargin: 5

            Label {
                anchors.centerIn: parent
                id:_unreadCount
                color: "white"
                font.pixelSize: 12
            }
        }
    }

    // 鼠标交互
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked:{
            var component  = Qt.createComponent("ChatWidget.qml");
            if (component.status === Component.Ready) {
                var chatWidget = component.createObject(parent);
                chatWidget.show();
             }
        }
    }

    // 分割线
    Rectangle {
        width: parent.width
        height: 1
        color: "#E6E6E6"
        anchors.bottom: parent.bottom
    }
}
