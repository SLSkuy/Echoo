//某个分组的好友

import QtQuick

Rectangle{
    property alias friendItem : friends_Item
    property alias friendlistmodel : listModel
    property alias friendstotal: _friendstotal
    id:_friendstotal
    visible: true
    ListView {
        id: friends_Item
        anchors.fill: parent
        model: listModel
        implicitHeight: parent.height
        spacing:5

        delegate:
            FriendItem{
                id:friendItem
                height: 40
                width: notification.width
                friendheadPortrait.source: model.headPortrait
                friendname.text: model.name
                friendpersonid: model.account

                friendTaphandler.onDoubleTapped: {
                    if (Qt.LeftButton && Qt.ControlModifier) {
                        if (friendItem.isSelected) {
                            friendItem.isSelected = false;
                            s1=0
                        } else {
                            friendItem.isSelected = true;
                            s1=1
                        }
                    }
                }

            }

    }

    ListModel {
        id: listModel
        ListElement {
            headPortrait: ""
            name: ""
            s1:0
            account:""
        }
    }

    Component.onCompleted: {
        listModel.clear();
        var netizen = EchooClient.getThisInfo();
        var friends = netizen.getFriends()
        for (var i = 0; i < friends.length; i++) {

                listModel.append({name: friends[i].nickname, s1: 0, account: friends[i].account})
            }
        // console.log(friends)
    }


}
