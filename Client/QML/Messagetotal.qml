import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../listmodels.js" as GlobalModels

Rectangle {
    property alias messagelistModel: msgListModel
    id: messagetotal
    // anchors.fill: parent
    implicitHeight: messageItem.implicitHeight
    implicitWidth: messageItem.implicitWidth


    ListView {
        id: messageItem
        anchors.fill: parent
        model: msgListModel
        clip: true
        spacing: 1  // 项间距

        delegate: MessageItem {
            implicitWidth: ListView.view.width
            implicitHeight: 60
            picture: model.picture
            nickname: model.name
            lastMessage: model.lastMessage
            time: model.time
            unreadCount: model.unreadCount
            isGroup: model._isGroup
            messageid: model.account
        }
    }

    ListModel {
        id: msgListModel
    }

    Component.onCompleted: {
        console.log("Initializing message list...")
        GlobalModels.messagelistModelinit(msgListModel)
        GlobalModels.messagelistModel = msgListModel

        var netizen = EchooClient.getThisInfo()

        var friends = netizen.getFriends()

        for (var i = 0; i < friends.length; i++) {
            var messages = EchooClient.getMessageList(friends[i].account)
            GlobalModels.addMessagelist(friends[i], messages)
        }
    }

    Connections {
        target: EchooClient
        function onReceivedFriendResponse(user, result) {
            if (result) {
                console.log("Adding new friend:", user.account)
                var messages = EchooClient.getMessageList(user.account)
                GlobalModels.addMessagelist(user, messages)
            }
        }
    }

    Connections {
        target: EchooClient
        function onAcceptFriendRequestnm(netizen, message) {
            console.log("Accepting friend request from:", netizen.account)
            GlobalModels.addMessagelist(netizen, message)
        }
    }
}
