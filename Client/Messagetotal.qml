import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// FrameLessWindow {
//     id: rootWindow
//     width: toolBars.width + titleBar.Layout.preferredWidth
//     height: toolBars.height
//     visible: true
//     // flags: Qt.FramelessWindowHint

//     RowLayout {
//         anchors.fill: parent

//         ToolBars {
//             id: toolBars
//             // message.texttext.color: "#007FFF"
//         }

//         Rectangle {
//             id: message
//             Layout.fillWidth: true
//             Layout.fillHeight: true

//             ColumnLayout {
//                 anchors.fill: parent

//                 MainpagetitleBar {
//                     id: titleBar
//                     Layout.preferredWidth:600
//                     minimizeButton.onClicked: rootWindow.showMinimized()
//                 }

//                 ListView {
//                     id: messageItem
//                     model: listModel
//                     // implicitWidth: 1000
//                     implicitHeight: parent.height
//                     implicitWidth: titleBar.width

//                     delegate:
//                         MessageItem{
//                             height:rootWindow.height/10
//                             // width: rootWindow.width - toolBars.width
//                             width:titleBar.width
//                             picture.source: picture1
//                             name.text: name1
//                             lastMessage.text: lastMessage1
//                             time.text: time1
//                             unreadCount.text: unreadCount1
//                         }

//                 }

//                 ListModel {
//                     id: listModel
//                     ListElement {
//                         picture1: ""
//                         name1: "李四"
//                         lastMessage1: "项目进展如何？"
//                         time1: "昨天"
//                         unreadCount1: 0
//                     }
//                     ListElement {
//                         picture1: ""
//                         name1: "张三"
//                         lastMessage1: "abc？"
//                         time1: "12：00"
//                         unreadCount1: 2
//                     }
//                 }
//             }
//         }
//     }
// }


Rectangle{
    visible: true
    anchors.fill: parent
    ListView {
            id: messageItem
            model: listModel
            // implicitWidth: 1000
            implicitHeight: parent.height
            implicitWidth: parent.width

            delegate:
                MessageItem{
                    height:parent.height/10
                    // width: rootWindow.width - toolBars.width
                    width:parent.width
                    picture.source: picture1
                    name.text: name1
                    lastMessage.text: lastMessage1
                    time.text: time1
                    unreadCount.text: unreadCount1
                }

        }

        ListModel {
            id: listModel
            ListElement {
                picture1: ""
                name1: "李四"
                lastMessage1: "项目进展如何？"
                time1: "昨天"
                unreadCount1: 0
            }
            ListElement {
                picture1: ""
                name1: "张三"
                lastMessage1: "abc？"
                time1: "12：00"
                unreadCount1: 2
            }
        }
}
