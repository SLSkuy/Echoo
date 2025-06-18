//单个群聊列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    property alias picture: _picture
    property alias nameGroup: _name
    property alias personcount: _personcount

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
        }

        Item{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignCenter
            RowLayout{
                // 群聊名称
                Label {
                    id:_name
                    color: "black"
                    font.pixelSize: 16
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                // 群聊人数
                Label {
                    Layout.alignment: Qt.AlignLeft
                    id: _personcount
                    font.pixelSize: 12
                    color: "darkgrey"
                }
            }
        }
    }

    // 鼠标交互
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked:{
            var component  = Qt.createComponent("GroupChat.qml");
            if (component.status === Component.Ready) {
                var groupchat = component.createObject(parent);
                groupchat.show();
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
