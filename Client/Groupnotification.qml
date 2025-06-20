import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

FrameLessWindow {
    id:chatwidget
    // visible: true
    width: 500
    height: 600

    // 主布局
    Column{
        id:column
        anchors.fill: parent
        spacing: 2

        TopBar{
            id:topbar
            Layout.alignment: Qt.AlignTop
            Layout.topMargin: 5
            text11.text:"群通知"
            text11.font.pixelSize: 18
        }

        Text{
            id: bin
            text: "🗑️"
            anchors.right: parent.right
            anchors.rightMargin: 8
            font.pixelSize: 18
            // color: hovered ? "red" : "transparent"
            TapHandler{
                onTapped:{
                    listModel.clear();
                }
            }
        }

        ListView {
            id: notification
            width: parent.width
            height: parent.height-bin.height-topbar.height
            model: listModel
            spacing: 5 // 项间距

            delegate: Rectangle {
                width: notification.width
                height: 60
                color: hoverHandler.hovered ? "#E6E6E6" : "transparent" // 悬停变灰

                //悬停变灰
                HoverHandler {
                    id: hoverHandler
                }
                RowLayout {
                    // anchors.fill: parent
                    spacing: 15

                    Image {
                        Layout.preferredWidth: 40
                        Layout.preferredHeight: 40
                        source: model.image1
                    }

                    ColumnLayout {
                        Layout.alignment: Qt.AlignLeft
                        Label {
                            text: model.name1
                            font.bold: true
                        }
                        RowLayout{
                            Label {
                                text: model.aaction1
                                color: "#666"
                            }
                            Label{
                                text: "  " + model.groupname
                                color:"blue"
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel{
        id: listModel
        ListElement{
            image1: ""
            name1: "111"
            aaction1: "加入"
            groupname: "abc"
        }
        ListElement{
            image1: ""
            name1: "111"
            aaction1: "退出"
            groupname: "abc"
        }
    }
}
