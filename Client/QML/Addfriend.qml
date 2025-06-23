import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    id:chatwidget
    width: 455

    ColumnLayout{
        anchors.fill: parent

        TopBar {
            id: topbarr
            Layout.preferredWidth: parent.height

            tcloseButton.onClicked: {
                search.text = ""  // 清除搜索内容
                chatwidget.close()
            }
        }

        TextField{
            Layout.preferredWidth: parent.height
            Layout.preferredHeight: 30
            id: search

            // text: ""
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
                width: parent.width
                height: parent.height

                delegate: Rectangle{
                    width:parent.width
                    height: parent.height/listModel.count
                    RowLayout{
                        anchors.fill: parent
                        Image{
                            source: source1
                            Layout.preferredWidth: 50
                            Layout.preferredHeight:50
                        }

                        Text {
                            id: name
                            Layout.topMargin: 40
                            Layout.leftMargin: 10
                            Layout.preferredHeight:parent.height
                            font.pixelSize: 18
                            text: name1
                        }
                        Text{
                            id: account
                            visible: false
                            text:account1
                        }

                        Button{
                            Layout.bottomMargin: 40
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredHeight:20
                            text:"加好友"
                            onClicked: {
                                enabled = false
                                EchooClient.addFriendRequest(account.text)
                                // console.log(account.text)
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
                // console.log(netizens[i].nickname)
                listModel.append({source1:"", name1: netizens[i].nickname, account1: netizens[i].account})
            }
        }
    }

    Component.onCompleted: searchnetizen()

}
