// MessageListView.qml
import QtQuick
import QtQuick.Controls

ListView {
    id: listView
    spacing: 5
    property alias model: listView.model
    property color myMessageColor: "#dcf8c6"
    property color otherMessageColor: "lightblue"
    property string myNickname: ""
    property string receiverName: ""

    delegate: Rectangle {
        width: messageText.implicitWidth+60
        height: Math.max(messageText.implicitHeight, imagemessage.height) + 10
        color: isMe ? myMessageColor : otherMessageColor
        radius: 5

        anchors.right: isMe ? parent.right : undefined
        anchors.left: isMe ? undefined : parent.left

        Text {
                id: messageText
                text: message
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                wrapMode: Text.Wrap
                color: "black"
            }

        Label {
            id: timeText
            text: isMe ? ( myNickname+ "  " +Qt.formatDateTime(new Date(), "hh:mm") ) : Qt.formatDateTime(new Date(), "hh:mm")+ "  " +receiverName
            //TODO
            color: "gray"
            font.pixelSize: 10
            anchors.bottom: messageText.top
            anchors.right: isMe ? parent.right : undefined
            anchors.left: isMe ? undefined : parent.left
            anchors.margins: 0
            visible: text !== ""
        }

        Image {
            id: imagemessage
            height:40
            width: 40
            anchors.top:parent.top
            anchors.topMargin: 10
            anchors.right: isMe ? parent.right : undefined
            anchors.left: isMe ? undefined : parent.left
        }
    }
}
