//某个分组的好友

import QtQuick

Rectangle{
    property alias friendItem : friendItem
    property alias friendlistmodel : listModel

    visible: true
    ListView {
        id: friendItem
        anchors.fill: parent
        model: listModel
        // implicitWidth: 1000
        implicitHeight: parent.height
        spacing:5

        delegate:
            FriendItem{
                id:mm
                height:friendItem.height/13
                width: parent.width
                friendheadPortrait.source: headPortrait1
                friendname.text: name1
                friendpersonid: id1

                friendTaphandler.onDoubleTapped: {
                    if (Qt.LeftButton && Qt.ControlModifier) {
                        if (mm.isSelected) {
                            mm.isSelected = false;
                            console.log("000");
                            s1=0
                        } else {
                            mm.isSelected = true;
                            console.log("11");
                            s1=1
                        }
                    }
                }

                // isSelected: s1
            }

    }

    ListModel {
        id: listModel
        ListElement {
            headPortrait1: ""
            name1: ""
            s1:0
            id1:""
        }
    }

    Component.onCompleted: {
        listModel.clear();
        var netizen = EchooClient.GetThisInfo();
        var friends = netizen.GetFriends()
        for (var i = 0; i < friends.length; i++) {

                listModel.append({name1: friends[i].nickname, s1: 0, id1: friends[i].account})
            }
        // console.log(friends)
    }


}
