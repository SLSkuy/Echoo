//单个分组

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id:root
    state: "hideState"

    implicitHeight: column.implicitHeight
    implicitWidth: column.implicitWidth

    property alias friendlist_text : text
    property alias more : more

    ColumnLayout{
        id:column
        anchors.fill: parent
        RowLayout{
            id:row
            Button{
                id: more
                background: Rectangle{
                    border.color: "transparent"
                }

                text: root.state === "hideState" ? ">" : "^"
                onClicked:
                {
                    root.state = (root.state === "hideState") ? "showState" : "hideState"
                }
            }

            Text{
                //列表名 目前只有一个
                id:text
            }
        }

        Friends{
            id:friends
            Layout.preferredHeight: root.height
            Layout.preferredWidth: root.width
        }
    }
    states: [
        State {
            name: "hideState"
            PropertyChanges {
                friends.visible: false
            }
        },
        State {
            name: "showState"
            PropertyChanges {
                friends.visible: true
            }
        }
    ]
}
