import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow{
    property alias username:_username
    property alias usernametext:_username.text
    property alias sex:_sex
    property alias signature:qm_nr
    property alias region:szd_nr
    property alias userheadPortrait:tx
    property string account
    id:personpage
    width:400
    height:300
    Component.onCompleted: {
        var n=EchooClient.getThisInfo();
        _username.text=n.nickname
        account = n.account
        // tx.source=n.GetAvatar()
    }

    ColumnLayout{
        // anchors.fill:parent
        RowLayout{
            Rectangle {
                Layout.topMargin:20
                Layout.leftMargin:10
                Layout.rightMargin:10
                width: 100
                height: 100
                radius: width / 2  // 使圆角半径等于宽度的一半
                color: "lightgrey"
                //TODO
                Image {
                    id: tx
                    anchors.fill:parent
                    // source: "qrc:/resources/LoginImage.png"
                    // source: "data:image/png;base64," + EchooClient.getThisInfo().avatar
                }
            }
            ColumnLayout{
                RowLayout{

                    Text{
                        id:_username


                    }
                    Text{
                        id:_sex
                        text: "\u2640"
                        color:"pink"
                    }
                }
                Text{
                    id:echoo_id
                    text:"id:" + account

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
                Text{
                    id:qm_nr
                    width:300
                    text:"            生活不止眼前的苟且，还有远方的苟且"
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
                Text{
                    id:szd_nr
                    text:"        中国重庆市"
                    font.pixelSize: 15
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true



                }
            }
        }


    }
    Button{
        id:bjzl
        text:"编辑资料"
        width:150
        anchors.bottomMargin:10
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.leftMargin:10




        property var editprofile: null // 用于存储 personpage 对象的引用
        property bool isEditProfileVisible: false // 用于跟踪窗口的可见性状态

        onClicked: {
            var component = Qt.createComponent("EditProfile.qml");
            if (component.status === Component.Ready) {
                if (editprofile === null) {
                    // 如果 personpage 尚未创建，则创建它
                    editprofile = component.createObject(null, {
                                                             flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
                                                         });
                    editprofile.visible = true; // 初始设置为可见
                    isEditProfileVisible = true;
                } else {
                    // 如果 editprofile 已经存在，切换其可见性
                    editprofile.visible = !isEditProfileVisible;
                    isEditProfileVisible = !isEditProfileVisible; // 更新状态
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
        enabled: false


    }

}
