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
                text: " \n  群通知\n"
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

                onClicked:{
                    var component  = Qt.createComponent("Groupnotification.qml");
                    if (component.status === Component.Ready) {
                        var groupnotification = component.createObject(parent);
                        groupnotification.show();
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

    ListView {
            id: messageItem
            Layout.preferredHeight: parent.height-groupmessage.height
            Layout.preferredWidth: parent.width
            Layout.leftMargin: 15
            // anchors.fill: parent
            model: listModel
            // width: 1000
            // height: parent.height
            // width: parent.width

            delegate:
               GroupItem{
                    height:parent.height/listModel.count
                    // width: rootWindow.width - toolBars.width
                    width:parent.width
                    picture.source: picture1
                    nameGroup.text: name1
                    personcount.text: count1
                }

        }

        ListModel {
            id: listModel
            ListElement {
                picture1: ""
                name1: "李四"
                count1: "(3)"
            }
            ListElement {
                picture1: ""
                name1: "张三"
                count1: "(6)"
            }
        }
    }
}
