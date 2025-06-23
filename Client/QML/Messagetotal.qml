import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: _messagetotal
    anchors.fill: parent

    ListView {
        id: messageItem
        anchors.fill: parent
        model: msgListModel

        delegate:
            MessageItem{
            id:item
            height:60
            width:parent.width
            picture: picture1
            nickname: name1
            lastMessage: lastMessage1
            time: time1
            unreadCount: unreadCount1
            isGroup: _isGroup
            messageid: account1
        }
    }

    ListModel {
        id: msgListModel
        // 初始化好友消息列表
        Component.onCompleted: {
            var netizen = EchooClient.getThisInfo();
            var friends = netizen.getFriends()
            for (var i = 0; i < friends.length; i++) {
                var messages = EchooClient.getMessageList(friends[i].account);
                msgListModel.append({
                    picture1:"",
                    name1: friends[i].nickname,
                    lastMessage1: messages[messages.length - 1].content,
                    time1: messages[messages.length - 1].timestamp,
                    unreadCount1: 0,
                    _isGroup:0,
                    account1: friends[i].account
                });
            }
        }
    }
}
