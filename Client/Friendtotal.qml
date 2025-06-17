//好友列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 40
            color: mouseArea.containsMouse ? "#E6E6E6" : "transparent"
            Label{
                id:groupmessage
                text: " \n  好友通知\n"
                // Layout.preferredHeight: 30
                // Layout.preferredWidth: parent.width
                // Layout.topMargin: 15
                // Layout.leftMargin: 15
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 16

            }
            // 鼠标交互
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true

                //点击组件就会弹出好友通知界面
                onClicked:{
                    var component  = Qt.createComponent("Friendnotification.qml");
                    if (component.status === Component.Ready) {
                        var friendnotification = component.createObject(parent);
                        friendnotification.show();
                     }
                }
        }
    }

    // 分割线
    Rectangle {
        width: parent.width
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 1
        color: "#E6E6E6"
    }

    //列出
    ListView {
        id: friendlist
        model: listModel
        implicitWidth: parent.width
        implicitHeight: parent.height

        delegate:
            Friendlist{
                height:parent.height/listModel.count
                width: parent.width
                text.text: text1
            }

    }

    ListModel {
        id: listModel
        ListElement {
            text1:"我的好友"
        }
    }
    }
}
