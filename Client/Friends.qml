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
                height:friendItem.height/13
                width: parent.width
                friendheadPortrait.source: headPortrait1
                friendname.text: name1
                friendsign.text: sign1
                friendpersonid: id1
                friendregion: region1

                // TapHandler{
                //     onDoubleTapped:{
                //         // s1 = 1

                //         console.log("hhhh")
                //     }
                // }
                friendmouseAreall.onDoubleClicked:{
                    s1=1;
                    console.log("jjj");
                }

                isSelected: s1
            }

    }

    ListModel {
        id: listModel
        ListElement {
            headPortrait1: "qrc:/resources/LoginImage.png"
            name1: "李四"
            sign1: "abc"
            s1:0
            id1:"111"
            region1:"重庆市"
        }
        ListElement {
            headPortrait1: "qrc:/resources/LoginImage.png"
            name1: "张三"
            sign1: "321"
            s1:0
            id1: "222"
            region1: "其他"
        }
    }
}
