import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Rectangle {
    // anchors.fill:parent
    id: titleBar
    width: parent.width
    height: 40
    color: "#333333"

    Text {
        id: titleText
        text: "编辑资料"
        color: "white"
        font.pixelSize: 16
        anchors.centerIn: parent
    }

    Button {
        text: "x"
        anchors {
            right: parent.right
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        flat: true
        contentItem: Text {
            text: parent.text
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: "transparent"
            Rectangle {
                width: parent.width
                height: 1
                color: "white"
                anchors.bottom: parent.bottom
                visible: parent.parent.hovered
            }
        }
        onClicked: {
            editprofile.close()
        }
    }
}
