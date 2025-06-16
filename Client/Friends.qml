import QtQuick

Rectangle{
    property alias friendItem : friendItem
    visible: true
    ListView {
        id: friendItem
        anchors.fill: parent
        model: listModel
        // implicitWidth: 1000
        implicitHeight: parent.height

        delegate:
            FriendItem{
                height:friendItem.height/10
                width: titleBar.width
                headPortrait.source: headPortrait1
                name.text: name1
                sign.text: sign1
            }

    }

    ListModel {
        id: listModel
        ListElement {
            headPortrait1: ""
            name1: "李四"
            sign1: "abc"
        }
        ListElement {
            headPortrait1: ""
            name1: "张三"
            sign1: "321"
        }
    }
}
