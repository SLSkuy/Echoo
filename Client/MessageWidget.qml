// MessageListView.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

ListView {
    id: listView
    spacing: 5

    // 定义属性以便外部可以设置
    property alias model: listView.model
    property color myMessageColor: "#dcf8c6"
    property color otherMessageColor: "lightblue"
    property string myNickname: ""

    delegate: Rectangle {
        width: parent.width/2
        height: messageText.implicitHeight + 20
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
            text: isMe ? ( startWindow.globalNicknametext+ "  " +Qt.formatDateTime(new Date(), "hh:mm") ) : Qt.formatDateTime(new Date(), "hh:mm")+ "  " +nameMessage.text
            color: "gray"
            font.pixelSize: 10
            anchors.bottom: messageText.top
            anchors.right: isMe ? parent.right : undefined
            anchors.left: isMe ? undefined : parent.left
            anchors.margins: 0
            visible: text !== ""
        }
    }
}
