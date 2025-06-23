import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../listmodels.js" as GlobalModels

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
        }
    }

    ListModel{
        id: msgListModel
    }

    // ListModel {
    //     id: msgListModel
        // 初始化好友消息列表
        Component.onCompleted: {
            GlobalModels.messagelistModelinit(msgListModel);
            GlobalModels.messagelistModel = msgListModel;

            console.log("[DEBUG] 全局模型 === 本地模型？",
                GlobalModels.messagelistModel === msgListModel);

            console.log("内存地址验证：",
                   "全局模型:", GlobalModels.messagelistModel,
                   "本地模型:", msgListModel,
                   "是否相同:", GlobalModels.messagelistModel === msgListModel);

               // 防止被其他代码篡改
            GlobalModels.messagelistModel.objectName = "LOCKED_MODEL";

            var netizen = EchooClient.getThisInfo();
            var friends = netizen.getFriends()
            for (var i = 0; i < friends.length; i++) {
                var messages = EchooClient.getMessageList(friends[i].account);
                GlobalModels.addMessagelist(friends[i],messages)
            }
        }

    Connections {
           target: EchooClient
           function onReceivedFriendResponse(user, result) {
               if(result){
                   var messages = EchooClient.getMessageList(user.account)
                   console.log("添加的好友： "+user.account)
                   GlobalModels.addMessagelist(user,messages)
               }
           }

       }

    Connections {
           target: EchooClient
           function onAcceptFriendRequestnm(netizen,message) {
                    GlobalModels.addMessagelist(netizen, message)
               }
           }
}
