//用于展示整个群聊列表

import QtQuick

Rectangle{
    ListView {
            id: messageItem
            anchors.fill: parent
            model: listModel
            // width: 1000
            // height: parent.height
            // width: parent.width

            delegate:
               GroupItem{
                    height:parent.height/listModel.count
                    width:parent.width
                    picture.source: picture1
                    name.text: name1
                    personcount.text: count1
                }

        }

        //测试
        ListModel {
            id: listModel
            ListElement {
                picture1: "qrc:/resources/LoginImage.png"
                name1: "李四"
                count1: "(3)"
            }
            ListElement {
                picture1: ""
                name1: "张三"
                count1: "(6)"
            }
            ListElement {
                picture1: ""
                name1: "王麻子"
                count1: "(5)"
            }
        }
}
