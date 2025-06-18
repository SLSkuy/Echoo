//消息列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    // property alias isGroup: _isGroup

    ListView {
            id: messageItem
            anchors.fill: parent
            model: listModel

            delegate:
                MessageItem{
                    id:item
                    height:parent.height/listModel.count
                    width:parent.width
                    picture.source: picture1
                    name.text: name1
                    lastMessage.text: lastMessage1
                    time.text: time1
                    unreadCount.text: unreadCount1
                    isGroup:_isGroup
                }

        }

        ListModel {
            id: listModel
            ListElement {
                picture1: "qrc:/resources/LoginImage.png"
                name1: "李四"
                lastMessage1: "项目进展如何？"
                time1: "昨天"
                unreadCount1: 0
                _isGroup: 1
            }
            ListElement {
                picture1: ""
                name1: "张三"
                lastMessage1: "abc？"
                time1: "12：00"
                unreadCount1: 2
                _isGroup: 0
            }
        }
}
