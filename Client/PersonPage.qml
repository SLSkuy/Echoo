import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FrameLessWindow{
    id:personpage
    width:400
    height:300
    x:20
    y:-200
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
                //后面改
                // Image {
                //     id: tx
                //     source: "qrc:/resources/LoginImage.png"
                // }
            }
            ColumnLayout{
                RowLayout{

                    Text{
                        id:username
                        text:"香菜ovo"
                    }
                    Text{
                        id:sex
                        text: "\u2640"
                        color:"pink"
                    }
                }
                Text{
                    id:echoo_id
                    text:"Echoo:123456"
                    //+loginform.id
                    font.pixelSize: 20
                }
                Text{
                    text:"🐷小猪也苦恼"
                    font.pixelSize: 15
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


    }
    Button{
        id:fsxx
        text:"发送消息"
        width:150
        anchors.bottom:parent.bottom
        anchors.bottomMargin:10
        anchors.right:parent.right
        anchors.rightMargin:10


    }

}
