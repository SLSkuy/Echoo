//单个好友

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id:friend_single
    // width: parent.width
    // height: parent.height/6

    property bool isSelected: false  // 新增选中状态
    property bool hovered
        color: {
            if (isSelected) {
                "lightblue"  // 选中状态保持蓝色
            } else if (hovered) {
                "#E6E6E6"  // 悬停时变灰
            } else {
                "transparent"  // 默认透明
            }
        }


    property alias friendheadPortrait : headPortrait
    property alias friendname : name
    property alias friendsign : sign
    property alias friendTaphandler: friendTaphandler
    property string friendpersonid: " "
    property string friendregion: " "

    RowLayout{
        id: row
        anchors.fill: parent
        spacing: 10
        // anchors.leftMargin: 1
        Image{
            id:headPortrait
            Layout.preferredHeight: 38
            Layout.preferredWidth: 38
            antialiasing: true
        }

        Item{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            ColumnLayout{
                id: column
                Layout.fillWidth: true
                Layout.topMargin: 10

                Text {
                    id: name
                    font.pixelSize: 16
                    color: "black"
                    Layout.alignment: Qt.AlignTop
                }

                Text {
                    id: sign
                    font.pixelSize: 10
                    color: "grey"
                    clip: true
                    // anchors.bottomMargin: 5
                    // anchors.left: headPortrait.right
                    visible: false
                }
            }
        }
    }

    HoverHandler {
        id: hoverHandler
        onHoveredChanged: friend_single.hovered = hovered
    }

    TapHandler{
        id:friendTaphandler
        property var friendpersonpage: null;
        onTapped: {
            if(!friendpersonpage) {
                var component = Qt.createComponent("Friendpersonpage.qml");
                if (component.status === Component.Ready) {
                    friendpersonpage = component.createObject(null, {
                            flags: Qt.Window | Qt.FramelessWindowHint
                    });
                }
            }
            friendpersonpage.show();
            friendpersonpage.raise(); // 关键：置顶窗口
            friendpersonpage.requestActivate(); // 激活窗口
        }

    }

}
