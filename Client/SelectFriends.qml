import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

FrameLessWindow {
    property alias selectfriends: _selectfriends
    id: _selectfriends
    width: 600
    height: 600

    ColumnLayout {
        anchors.fill: parent

        SelectTitleBar {
            id: et
            Layout.preferredWidth: parent.width
        }

        RowLayout {
            Layout.preferredWidth: 600
            Layout.preferredHeight: 560

            // 左侧好友列表 (fs)
            Friends {
                id: fs
                Layout.preferredWidth: 300
                Layout.preferredHeight: 560
            }

            // 右侧已选好友列表
            Rectangle {
                Layout.preferredWidth: 300
                Layout.preferredHeight: 560
                color: "#f0f0f0"

                Label {
                    id: label
                    text: "已选中"
                    font.bold: true
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 5
                }

                ListView {
                    id: friendItem
                    anchors.top: label.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 5
                    model: listModel
                    spacing: 5
                    clip: true

                    delegate: FriendItem {
                        height: 50
                        width: parent.width
                        headPortrait.source: headPortrait1
                        name.text: name1
                        sign.text: sign1
                        isSelected: true // 右侧列表中的项默认选中
                    }
                }

                ListModel { id: listModel }

                Button {
                    text: "更新已选好友"
                    onClicked: updateSelectedFriends()
                }


            }

        }
    }
    // 更新已选好友列表
    function updateSelectedFriends() {
            listModel.clear()
            console.log("lllll")
            for (var i = 0; i < fs.friendlistmodel.count; i++) {
                var item = fs.friendlistmodel.get(i);
                // item.s1 = 1
                console.log("Item at index " + i + ": " + item.name1.text);
                if (item.s1) {
                    listModel.append({
                        // headPortrait1: item.headPortrait.source,
                        name1: item.name1,
                        sign1: "item.sign.text",
                        // color:"black"
                    })
                }
            }
        }

}
