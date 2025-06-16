import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id:root
    // anchors.top: parent.top
    // width: parent.width
    // height: parent.height/15
    state: "hideState"

    // property alias group : group
    property alias text : text
    property alias more : more
    // property alias friends : friends

    ColumnLayout{
        // anchors.top: parent.top
        anchors.fill: parent
        RowLayout{
            id:group
            Button{
                id: more
                background: Rectangle{
                    border.color: "transparent"
                }

                text: root.state === "hideState" ? ">" : "^"
                // text:">"
                onClicked:
                {
                    root.state = (root.state === "hideState") ? "showState" : "hideState"
                    // flags: Qt.WindowStaysOnTopHint
                }
            }

            Text{
                id:text
            //     text:"列表名"
            }
        }

        Friends{
            id:friends
            // Layout.fillHeight: true
            // Layout.fillHeight: true
            height: rootWindow.height - titleBar.height
            // z:1000
            width: titleBar.width

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
