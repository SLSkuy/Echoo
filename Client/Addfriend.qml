import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FrameLessWindow {
    id:chatwidget
    width: 455
    ColumnLayout{
        anchors.fill: parent

        TopBar{
            id:topbarr
            Layout.preferredWidth: parent.height
        }

        TextField{
            Layout.preferredWidth: parent.height
            Layout.preferredHeight: 30
            id: search

            placeholderText:"🔍 搜索 "
            placeholderTextColor: "gray"
            background:Rectangle{
                color: "#F0F0F0"
                border.color: search.focus ? "#00BFFF" :"transparent"
            }
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
                        Button{
                            Layout.bottomMargin: 40
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredHeight:20
                            text:"加好友"
                            onClicked: {
                                //TODO
                                enabled = false
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
            source1: ""
            name1:"abc"
        }
        ListElement{
            source1: ""
            name1:"123"
        }
    }
}
