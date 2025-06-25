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
    property string receiverName: receivername
    // property alias messageConte: message
    // property alias picture: picture

    delegate: Rectangle {
        width: messageText.text === "" ? Math.max(messageText.implicitWidth + 10, imagemessage.width + 10): imagemessage.width + 20
        height: messageText.text === "" ? Math.max(messageText.implicitHeight + 10, imagemessage.height + 10):implicitHeight+40
        color: isMe ? myMessageColor : otherMessageColor
        radius: 5

        anchors.right: isMe ? parent.right : undefined
        anchors.left: isMe ? undefined : parent.left
        anchors.rightMargin : isMe ? 10 : undefined
        anchors.leftMargin : isMe ? undefined : 10

        Text {
                id: messageText
                text: message
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10
                wrapMode: Text.Wrap
                color: "black"
            }

        Label {
            id: timeText
            text: isMe ? ( myNickname+ "  " +Qt.formatDateTime(new Date(), "hh:mm") ) : Qt.formatDateTime(new Date(), "hh:mm")+ "  " +receivername
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
            height:150
            width: 200
            anchors.top:parent.top
            // anchors.topMargin: 10
            fillMode: Image.PreserveAspectFit
            anchors.right: isMe ? parent.right : undefined
            anchors.left: isMe ? undefined : parent.left
            // source: "qrc:/resources/LoginImage.png"
            source: picture
            visible: picture !== ""

        }
    }
}
