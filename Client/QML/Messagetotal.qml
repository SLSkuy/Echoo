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
            unreadCountContainer.visible: model.unread
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
        function onRemovemessagList(user){
            account=user.account;
            for (var i = 0; i < messagetotal.messagelistModel.count; i++) {
                var item = messagetotal.messagelistModel.get(i);
                if (item.account === account) {
                    messagetotal.messagelistModel.remove(i);
                    break;
                }
            }
        }
    }


    Connections {
        target: EchooClient
        function onMessageReceived(msg) {
            var netizen = EchooClient.getThisInfo()
            for(var i = 0; i < msgListModel.count; i++){
                if(msgListModel.get(i).account === msg.sender.account){
                    msgListModel.set(i, {
                                         picture:  msgListModel.get(i).picture,
                                         name: msgListModel.get(i).name,
                                         account: msgListModel.get(i).account,
                                         lastMessage: msg.content,
                                         time: new Date().toLocaleString(),
                                         unreadCount: 1,
                                         _isGroup:msgListModel.get(i)._isGroup,
                                         unread: 1
                                     })
                    msgListModel.move(i, 0, 1);
                }
            }
        }

        function onImgReceived(msg){
            var netizen = EchooClient.getThisInfo()
            for(var i = 0; i < msgListModel.count; i++){
                if(msgListModel.get(i).account === msg.sender.account){
                    msgListModel.set(i, {
                                         picture: msgListModel.get(i).picture,
                                         name: msgListModel.get(i).name,
                                         account: msgListModel.get(i).account,
                                         lastMessage: "[图片]",
                                         time: new Date().toLocaleString(),
                                         unreadCount: 1,
                                         _isGroup:msgListModel.get(i)._isGroup,
                                         unread: 1
                                     })
                    // console.log(unreadCount);
                    msgListModel.move(i, 0, 1);
                }
            }
        }

        function onTriggerMessage(receiverAccount, content){
            var messages = EchooClient.getMessageList(receiverAccount)
            var netizen = EchooClient.getThisInfo()
            // var friends = netizen.getFriends()
            for(var i = 0; i < msgListModel.count; i++){
                if(msgListModel.get(i).account === receiverAccount){
                    msgListModel.set(i, {
                                         picture:  msgListModel.get(i).picture,
                                         name: msgListModel.get(i).name,
                                         account: msgListModel.get(i).account,
                                         lastMessage: content,
                                         time: new Date().toLocaleString(),
                                         unreadCount: msgListModel.get(i).unreadCount + 1,
                                         _isGroup:msgListModel.get(i)._isGroup,
                                         unread: 0
                                     })
                    msgListModel.move(i, 0, 1);
                    console.log("111111111111");
                }
                console.log(i);
            }
        }

        function onTriggerImage(receiverAccount, imgPath){
            var messages = EchooClient.getMessageList(receiverAccount)
            var netizen = EchooClient.getThisInfo()
            // var friends = netizen.getFriends()
            for(var i = 0; i < msgListModel.count; i++){
                if(msgListModel.get(i).account === receiverAccount){
                    msgListModel.set(i, {
                                         picture:  msgListModel.get(i).picture,
                                         name: msgListModel.get(i).name,
                                         account: msgListModel.get(i).account,
                                         lastMessage: "[图片]",
                                         time: new Date().toLocaleString(),
                                         unreadCount: msgListModel.get(i).unreadCount + 1,
                                         _isGroup:msgListModel.get(i)._isGroup,
                                         unread: 0
                                     })
                    msgListModel.move(i, 0, 1);
                }
            }
        }
    }
}
