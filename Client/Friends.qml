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
                friendsign.text: sign1
                friendpersonid: id1
                friendregion: region1

                friendTaphandler.onDoubleTapped: {
                    if ((mouse.buttons & Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier)) {
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
