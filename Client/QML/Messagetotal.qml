import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    property alias messagetotal: _messagetotal
    property alias messagelistModel: msgListModel
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
            picture: model.picture
            nickname: model.name
            lastMessage: model.lastMessage
            time: model.time
            unreadCount: model.unreadCount
            isGroup: model._isGroup
            messageid: model.account
            focus: true
            enabled: true
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
                    picture:"",
                    name: friends[i].nickname,
                    lastMessage: messages[messages.length - 1].content,
                    time: messages[messages.length - 1].timestamp,
                    unreadCount: 0,
                    _isGroup:0,
                    account: friends[i].account
                });
            }
        }
    }
}
