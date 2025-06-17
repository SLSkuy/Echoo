//单个好友

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id:friend_single
    // width: parent.width
    // height: parent.height/6

    // color: hovered ? "grey" : "transparent"
    // color: "black"
    color: mouseArea.containsMouse ? "#E6E6E6" : "transparent"

    property alias headPortrait : headPortrait
    property alias name : name
    property alias sign : sign

    RowLayout{
        id: row
        anchors.fill: parent
        spacing: 10
        // anchors.leftMargin: 1
        Image{
            id:headPortrait
            Layout.preferredHeight: 38
            Layout.preferredWidth: 38
            antialiasing: true
        }

        Item{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            ColumnLayout{
                id: column
                Layout.fillWidth: true
                Layout.topMargin: 10

                Text {
                    id: name
                    font.pixelSize: 16
                    color: "black"
                    Layout.alignment: Qt.AlignTop
                }

                Text {
                    id: sign
                    font.pixelSize: 10
                    color: "grey"
                    clip: true
                    // anchors.bottomMargin: 5
                    // anchors.left: headPortrait.right
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

    }

}
