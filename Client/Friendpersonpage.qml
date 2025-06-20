import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow{
    property alias usernameFriend:_username
    property alias sexFriend:_sex
    property alias signatureFriend:qm_nr
    property alias regionFriend:szd_nr
    property alias headPortraitFriend:tx
    property alias friendPersonpage: chatwidget

    id:chatwidget
    width:400
    height:300


    ColumnLayout{
        anchors.fill:parent
        TopBar{
            Layout.preferredWidth: parent.width
            text11.text: "个人主页"
        }

        RowLayout{
            Rectangle {
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                width: 100
                height: 100
                radius: width / 2  // 使圆角半径等于宽度的一半
                color: "lightgrey"
                //后面改
                Image {
                    id: tx
                    anchors.fill:parent
                    source: "qrc:/resources/LoginImage.png"
                }
            }
            ColumnLayout{
                RowLayout{

                    Text{
                        id:_username
                        text:name.text
                    }
                    Text{
                        id:_sex
                        text: "\u2640"
                        color:"pink"
                    }
                }
                Text{
                    id:echoo_id
                    text:"id:"+friendpersonid

                    font.pixelSize: 20
                }
            }
        }
        RowLayout{
            Text{
                id:qm
                text:"签名"
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter

            }
            Rectangle{
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 61
                Text{
                    id:qm_nr
                    width:300
                    text:friendsign.text
                    font.pixelSize: 15
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true



                }
            }
        }
        RowLayout{
            Text{
                id:szd
                text:"所在地"
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter

            }
            Rectangle{
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 42
                Text{
                    id:szd_nr
                    text: friendregion
                    font.pixelSize: 15
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true



                }
            }
        }


    }

    Button{
        id:fsxx
        text:"发送消息"
        width:150
        anchors.bottom:parent.bottom
        anchors.bottomMargin:10
        anchors.right:parent.right
        anchors.rightMargin:10

        //单机“发消息”按钮，弹出聊天框
        property var chatWidget: null;
        onClicked: {
            if(!chatWidget) {
                var component = Qt.createComponent("ChatWidget.qml");
                if (component.status === Component.Ready) {
                    chatWidget = component.createObject(null, {
                        flags: Qt.Window | Qt.FramelessWindowHint, account:echoo_id
                    });
                }
            }
            chatWidget.topBar.text11.text = usernameFriend.text
            chatWidget.show();
            chatWidget.raise(); // 关键：置顶窗口
            chatWidget.requestActivate(); // 激活窗口
            // unreadCount.text = "0"; //点击进聊天界面就会让未读消息清零
        }

    }

}
