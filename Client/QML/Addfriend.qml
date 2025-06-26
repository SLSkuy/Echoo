import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    // property alias addButton: addButton
    id:addFriend
    width: 455
    property bool isfriend: false

    ColumnLayout{
        anchors.fill: parent

        Rectangle {
            id: titleBar
            Layout.preferredWidth: parent.height
            height: 40
            color: "transparent"  // 标题栏背景颜色

            RowLayout {
                anchors.fill: parent

                // 窗口标题
                Text {
                    id:text
                    text: "好友通知"
                    color: "black"
                    font.pixelSize: 14
                    Layout.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                }

                Item {
                    Layout.fillWidth: true  // 占位符，将按钮推到右侧
                }

                // 最小化按钮
                Button {
                    id: minimizeButton
                    text: "—"

                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: addFriend.showMinimized()
                    background: Rectangle {
                        color: "transparent"  // 设置背景颜色为透明
                        border.color: "transparent"  // 设置边框颜色为透明
                        border.width: 2
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // 最大化/还原按钮
                Button {
                    id: maximizeButton
                    text: addFriend.visibility === Window.Maximized ? "r" : "+"
                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: {
                        if (addFriend.visibility === Window.Maximized) {
                            addFriend.showNormal()
                        } else {
                            addFriend.showMaximized()
                        }
                    }
                    background: Rectangle {
                        color: "transparent"
                        border.color: "transparent"
                        border.width: 2
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // 关闭按钮
                Button {
                    id: closeButton
                    text: "x"
                    width: 25
                    Layout.preferredHeight: 20
                    onClicked: {
                        search.text = ""  // 清除搜索内容
                        addFriend.close()
                    }
                    background: Rectangle {
                        color: "transparent"
                        border.color: "transparent"
                        border.width: 2
                    }
                    contentItem: Text {
                        text: parent.text
                        color: parent.hovered ? "red" : "black"  // 悬停时文本变为红色
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        TextField{
            Layout.preferredWidth: parent.height
            Layout.preferredHeight: 30
            id: search

            placeholderText:"🔍 搜索      请输入完整的账号查找"
            placeholderTextColor: "gray"
            background:Rectangle{
                color: "#F0F0F0"
                border.color: search.focus ? "#00BFFF" :"transparent"
            }

            onTextChanged: searchnetizen()

        }
        Rectangle{
            id:display
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true

            ListView{
                model: listModel
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height

                delegate: Rectangle{
                    width:ListView.view.width
                    // height: parent.height/listModel.count
                    height: 40
                    RowLayout{
                        anchors.fill: parent
                        Image{
                            source: model.source
                            Layout.preferredWidth: 50
                            Layout.preferredHeight:50
                        }

                        Text {
                            id: name
                            Layout.topMargin: 40
                            Layout.leftMargin: 10
                            Layout.preferredHeight:parent.height
                            font.pixelSize: 18
                            text: model.name
                        }
                        Text{
                            id: account
                            visible: false
                            text:model.account
                        }

                        Button{
                            id: addButton
                            Layout.bottomMargin: 40
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredHeight:20
                            enabled: isfriend ? false : true
                            text:isfriend ? "已是好友" : "加好友"
                            onClicked: {
                                enabled = false
                                EchooClient.addFriendRequest(account.text)
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel{
        id: listModel
    }

    function searchnetizen() {
        listModel.clear()
        var netizens = EchooClient.getNetizenList()
        for(var i = 0; i < netizens.length; i++){
            if(netizens[i].account === search.text){
                listModel.append({source:netizens[i].avatar, name: netizens[i].nickname, account: netizens[i].account})
            }
        }
        var myself = EchooClient.getThisInfo();
        var friends = myself.getFriends()
        for (var j = 0; j < friends.length; j++) {
                if(search.text === friends[j].account)
                    isfriend = true
            }
    }

    Component.onCompleted: searchnetizen()

}
