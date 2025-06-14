import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window

// FrameLessWindow{
//     // height: toolbar.implicitHeight
//     // width: toolbar.implicitWidth

    Rectangle{
        id: toolbar
        implicitHeight:800; implicitWidth: 60
        visible: true
        color: "#D3D3D3"

        property alias app: app
        property alias headPortrait: headPortrait
        property alias collection: collection
        property alias more: more
        property alias dynamic: dynamic
        property alias file: file
        property alias friend: friend
        property alias email: email
        property alias manage: manage
        property alias message: message

        ColumnLayout{
            spacing: 10
            anchors.fill: parent
            Layout.alignment: Qt.AlignTop
            Rectangle{
                id: app
                // anchors.horizontalCenter: parent.horizontalCenter
                Layout.topMargin: 10
                Layout.leftMargin:3
                color: "transparent"
                Text{
                    text:"Echoo"
                    color: "black"
                    font.bold: true
                    font.pixelSize: 16
                    anchors.left: parent.left
                }
            }
            Rectangle{
                id:headPortrait
                // anchors.horizontalCenter: parent.horizontalCenter
                Layout.preferredHeight:50
                Layout.preferredWidth:50
                Layout.leftMargin:5
                radius: width/2
                Text{
                    text:"  \n  头像"
                }
                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true

                    property var personpage: null // 用于存储 personpage 对象的引用
                        property bool isPersonPageVisible: false // 用于跟踪窗口的可见性状态

                        onClicked: {
                            var component = Qt.createComponent("PersonPage.qml");
                            if (component.status === Component.Ready) {
                                if (personpage === null) {
                                    // 如果 personpage 尚未创建，则创建它
                                    personpage = component.createObject(null, {
                                        flags: Qt.WindowStaysOnTopHint
                                    });
                                    personpage.visible = true; // 初始设置为可见
                                    isPersonPageVisible = true;
                                } else {
                                    // 如果 personpage 已经存在，切换其可见性
                                    personpage.visible = !isPersonPageVisible;
                                    isPersonPageVisible = !isPersonPageVisible; // 更新状态
                                }
                            }
                        }
                }

                Image {
                    id: myself
                    // source: "file"
                }
            }
            Button{
                id: message
                text: "📳"
                property alias texttext: texttext
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: message.hovered ? "grey" : (message.focus ? "skyblue" : "transparent")
                    color: message.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                id: texttext
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:friend
                text:"👩"
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: friend.hovered ? "grey" : (friend.focus ? "skyblue" : "transparent")
                    color: friend.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:dynamic
                text:"🔯"
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: dynamic.hovered ? "grey" : (dynamic.focus ? "skyblue" : "transparent")
                    color: dynamic.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:manage
                text:" ... "
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: manage.hovered ? "grey" : (manage.focus ? "skyblue" : "transparent")
                    color: manage.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:email
                text:"📨"
                Layout.topMargin: 50
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: email.hovered ? "grey" : (email.focus ? "skyblue" : "transparent")
                    color: email.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:file
                text:"📁"
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: file.hovered ? "grey" : (file.focus ? "skyblue" : "transparent")
                    color: file.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:collection
                text:"💟"
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: collection.hovered ? "grey" : (collection.focus ? "skyblue" : "transparent")
                    color: collection.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
            Button{
                id:more
                text:"〰️"
                Layout.preferredHeight:40
                Layout.preferredWidth:40
                Layout.leftMargin:10
                // anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    // color: more.hovered ? "grey" : (more.focus ? "skyblue" : "transparent")
                    color: more.hovered ? "grey" : "transparent"
                }
                contentItem: Text {
                                text: parent.text
                                color: parent.focus ? "#007FFF" : "black"  // 悬停时文本变为蓝色
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 20
                }
            }
        }
    }
// }
