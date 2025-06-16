import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id:friend_single
    // width: parent.width
    // height: parent.height/6

    color: friend_single.hovered ? "grey" : "transparent"
    // color: "black"

    property alias headPortrait : headPortrait
    property alias name : name
    property alias sign : sign

    RowLayout{
        id: row
        anchors.fill: parent
        // anchors.leftMargin: 1
        Image{
            id:headPortrait
            // source: ""
            height: parent.height*5/6
            width: parent.width/13
            antialiasing: true
        }

        ColumnLayout{
            id: column

            Text {
                id: name
                // text: qsTr(" ")
                font.pixelSize: 16
                color: "black"
                anchors.topMargin: 5
            }

            Text {
                id: sign
                // text: qsTr("text")
                font.pixelSize: 10
                color: "grey"
                clip: true
                anchors.bottomMargin: 5
            }
        }
    }

}
