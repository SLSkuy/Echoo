//好友列表

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// FrameLessWindow {
//     property  alias rootWindow: rootWindow
//     property  alias titleBar : titleBar
//     id: rootWindow
//     width: toolBars.width + titleBar.Layout.preferredWidth
//     height: toolBars.height
//     visible: true
//     flags: Qt.FramelessWindowHint

//     RowLayout {
//         anchors.fill: parent

//         ToolBars {
//             id: toolBars
//             // message.texttext.color: "#007FFF"
//         }

//         Rectangle {
//             id: friend
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
//                     id: friendlist
//                     model: listModel
//                     implicitWidth: titleBar.width
//                     implicitHeight: parent.height

//                     delegate:
//                         Friendlist{
//                             height:rootWindow.height/15
//                             Layout.fillWidth: true
//                             text.text: text1
//                         }

//                 }

//                 ListModel {
//                     id: listModel
//                     ListElement {
//                         text1:"我的好友"
//                     }
//                 }
//             }
//         }
//     }
// }

Rectangle{
    ListView {
        id: friendlist
        model: listModel
        implicitWidth: parent.width
        implicitHeight: parent.height

        delegate:
            Friendlist{
                height:parent.height/listModel.count
                width: parent.width
                text.text: text1
            }

    }

    ListModel {
        id: listModel
        ListElement {
            text1:"我的好友"
        }
    }
}
