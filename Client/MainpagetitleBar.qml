//主页面的标题栏
//位于主页面的上方

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts



// Window {

//     id: window
//     // width: 700
//     // height: aaa.implicitHeight
//     visible: true
//     flags: Qt.FramelessWindowHint | Qt.Window

    ColumnLayout{
        id:aaa
        // anchors.fill: parent
        spacing: 5

        property alias minimizeButton: minimizeButton

        RowLayout{
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true

            TapHandler{
                onTapped:console.log(parent.width)
            }
            Button {
                id: minimizeButton
                text: "—"
                implicitHeight: 35
                implicitWidth: 35
                Layout.preferredHeight: 20
                // onClicked: window.showMinimized()
                background: Rectangle{
                    color: minimizeButton.hovered ? "gray" : "transparent"
                    border.color: "transparent"
                }
            }

            Button{
                id: closeButton
                text: "×"

                implicitHeight: 35
                implicitWidth: 35
                Layout.rightMargin: 5

                onClicked: Qt.quit()

                background: Rectangle{
                    color: closeButton.hovered ? "red" : "transparent"
                    border.color: "transparent"
                }

            }
        }

        RowLayout{
            id: row1
            spacing: 5

            // TapHandler{
            //     onTapped:console.log(parent.width)
            // }

            TextField{
                id: search
                // Layout.topMargin: 30
                Layout.fillWidth: true
                Layout.leftMargin:12
                Layout.bottomMargin:10
                Layout.preferredWidth:parent.implicitWidth -row1.spacing - search.Layout.leftMargin - morebutton.Layout.rightMargin -morebutton.implicitWidth
                implicitHeight: 30
                // text: "🔍"
                placeholderText:"🔍 搜索 "
                placeholderTextColor: "gray"
                background:Rectangle{
                    color: "#F0F0F0"
                    border.color: search.focus ? "#00BFFF" :"transparent"
                }

                Button{
                    id: clearButton
                    background:Rectangle{
                        color: clearButton.hovered ? "lightgray" : "#F0F0F0"
                    }
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    text: "x"
                    onClicked:
                    search.text = ""
                    opacity: search.focus ? 1 :0
                }
            }

            Button{
                id: morebutton
                // Layout.topMargin: 30
                Layout.rightMargin: 12
                Layout.bottomMargin:10
                text: "+"
                implicitWidth:30
                implicitHeight: 30
                ToolTip {
                    id: add
                    text: "加好友"
                    visible: parent.hovered
                    delay: 500 // 悬停500毫秒后显示
                }
                background:Rectangle{
                    // color: "#F0F0F0"
                    color: morebutton.hovered ? "lightgrey" : (morebutton.focus ? "#BEBEBE" : "#F0F0F0")
                }
                property var addfriend: null;
                onClicked: {
                    if(!addfriend) {
                        var component = Qt.createComponent("Addfriend.qml");
                        if (component.status === Component.Ready) {
                            addfriend = component.createObject(null, {
                                flags: Qt.Window | Qt.FramelessWindowHint
                            });
                        }
                    }
                    addfriend.show();
                    addfriend.raise(); // 关键：置顶窗口
                    addfriend.requestActivate(); // 激活窗口
                }
            }
        }
    }
// }
