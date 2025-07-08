//某个分组的好友

import QtQuick
import "../listmodels.js" as GlobalModels

Rectangle{
    property alias friendsItem : friends_Item
    property alias friendlistmodel : listModel
    property alias friendstotal: _friendstotal

    id:_friendstotal
    visible: true

    implicitHeight: friends_Item.implicitHeight
    implicitWidth: friends_Item.implicitWidth
    ListView {
        id: friends_Item
        anchors.fill: parent

        model: listModel
        // model: GlobalModels.friendlistModel
        height: parent.height
        spacing:5

        delegate:
            FriendItem{
            id:friendItem
            height: 40
            width: notification.width
            friendheadPortrait.source: model.headPortrait
            friendname.text: model.name
            friendpersonid: model.account
            friendsign.text: model.sign

            friendTaphandler.onDoubleTapped: {
                if (Qt.LeftButton && Qt.ControlModifier) {
                    if (friendItem.isSelected) {
                        friendItem.isSelected = false;
                        // s1=0
                    } else {
                        friendItem.isSelected = true;
                        // s1=1
                    }
                }
            }

        }

    }

    ListModel {
        id: listModel

    }

    Component.onCompleted: {
        GlobalModels.friendlistModelinit(listModel);
        GlobalModels.clearfriendModel(listModel);
        var netizen = EchooClient.getThisInfo();
        var friends = netizen.getFriends()
        for (var i = 0; i < friends.length; i++) {
            GlobalModels.addFriend(friends[i])
        }
    }

    Connections {
        target: EchooClient
        function onReceivedFriendResponse(user, result) {
            if(result){
                var messages = EchooClient.getMessageList(user.account)
                console.log("添加的好友： "+user.account)
                GlobalModels.addFriend(user)
            }
        }

    }
    Connections {
        target: EchooClient
        function onAcceptFriendRequestn(netizen) {
            GlobalModels.addFriend(netizen)
            console.log("niaccpectlema")
        }
    }




    // Connections {

    //     target:EchooClient

    //     function onRemoveFriendsSignals(account){
    //         for (var j = 0; j < friendstotal.friendlistmodel.count; j++) {
    //             var item1 = friendstotal.friendlistmodel.get(j);
    //             if (item1.account === account) {
    //                 if(friendPersonpage){
    //                     console("删除已存在的好友主页");
    //                     friendPersonpage.close();
    //                 }
    //                 friendstotal.friendlistmodel.remove(j);
    //                 console.log("delete")
    //                 break;
    //             }
    //         }
    //     }


    // }


}






