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
            ColumnLayout{
                Label{
                    text:"ctrl+双击左键可自由选择"
                    font.pixelSize: 10
                }

                // 左侧好友列表 (fs)
                Friends {
                    id: fs
                    Layout.preferredWidth: 300
                    Layout.preferredHeight: 520
                }
            }



            // 右侧已选好友列表
            Rectangle {
                id:rf
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
                        friendheadPortrait.source: headPortrait1
                        friendname.text: name1
                        friendsign.text: sign1
                        isSelected: true // 右侧列表中的项默认选中
                    }
                }

                ListModel { id: listModel }

                Button {
                    text: "更新已选好友"
                    anchors.right:rf.right
                    anchors.rightMargin:10

                    onClicked: updateSelectedFriends()
                }
                RowLayout{
                    anchors.bottom:rf.bottom
                    anchors.bottomMargin:10
                    width: parent.width
                    Button{
                        text:"确定"
                        Layout.bottomMargin:10
                    }
                    Button{
                        text:"取消"
                        Layout.bottomMargin:10
                        Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                        Layout.rightMargin:10
                        onClicked:_selectfriends.close()
                    }
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
                // console.log("Item at index " + i + ": " + item.name1.text);
                if (item.s1) {
                    listModel.append({
                        headPortrait1: item.headPortrait1,
                        name1: item.name1,
                        sign1: item.sign1,
                        // color:"black"
                    })
                }
            }
        }

}
