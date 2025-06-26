//主页面的标题栏
//位于主页面的上方

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout{
    id: mainpage
    property alias minimizeButton: minimizeButton

    RowLayout{
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        // Layout.rightMargin: 5
        Layout.fillHeight: true
        spacing: 0

        // 最小化按钮
        Button {
            id: minimizeButton
            text: "—"
            Layout.preferredHeight: 35
            Layout.preferredWidth: 35
            background: Rectangle{
                color: minimizeButton.hovered ? "gray" : "transparent"
                border.color: "transparent"
            }
        }

        // 关闭程序按钮
        Button{
            id: closeButton
            text: "×"
            Layout.preferredHeight: 35
            Layout.preferredWidth: 35
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

        TextField{
            id: search
            Layout.fillWidth: true
            Layout.leftMargin:12
            Layout.bottomMargin:10
            Layout.preferredWidth:parent.width -row1.spacing - search.Layout.leftMargin - morebutton.Layout.rightMargin -morebutton.width
            Layout.preferredHeight: 30
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
