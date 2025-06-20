//消息列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    // property alias isGroup: _isGroup
    property alias messageItem : messageItem

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
                    nameMessage.text: name1
                    lastMessage.text: lastMessage1
                    time.text: time1
                    unreadCount.text: unreadCount1
                    isGroup:_isGroup
                }

        }

        ListModel {
            id: listModel
            ListElement {
                picture1: ""
                name1: ""
                lastMessage1: ""
                time1: ""
                unreadCount1: 0
                _isGroup: 1
            }
        }


        Component.onCompleted: {
            listModel.clear();
            var netizen = EchooClient.GetThisInfo();
            var friends = netizen.GetFriends()
            // console.log(friends[1].nickname)
            for (var i = 0; i < friends.length; i++) {
                    var messages = EchooClient.GetMessageList(friends[i].account)
                // console.log(messages[messages.length-1])
                // console.log(messages[messages.length-1].timestamp)
                    listModel.append({name1: friends[i].nickname, lastMessage1: messages[messages.length-1].content, time1: messages[messages.length-1].timestamp,
                                         unreadCount1: 0,_isGroup: 1})

                }

        }
}
