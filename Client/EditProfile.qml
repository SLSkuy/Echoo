import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

FrameLessWindow {
    property alias editprofile: _editprofile
    width: 400
    height: 400
    visible: true
    id: _editprofile

    EditTitle {
        id: edittitle
    }

    ColumnLayout {
        anchors.top: edittitle.bottom
        width: parent.width
        spacing: 10

        Rectangle {
            id: tx
            width: 400
            height: 100
            Image {
                width: 80
                height: 80
                anchors.topMargin: 20
                anchors.centerIn: parent
                source: "qrc:/resources/LoginImage.png"
            }
        }

        // 单个输入项（昵称）
        RowLayout {
            width: parent.width

            Item{
                width:60
            }

            // 标签（昵称）
            Text {
                text: "昵称:"
                color: "black"
                font.pixelSize: 16
                Layout.preferredWidth: 40  // 固定宽度
            }

            // 输入框
            TextField {
                id: nicknameField
                placeholderText: "请输入昵称"
                placeholderTextColor:"lightgrey"
                font.pixelSize: 16
                color: "black" // 文字颜色
                background: Rectangle {
                    border.color:"#A0A0A0"
                    color: "white"
                }
                Layout.fillWidth: true  // 填充剩余的宽度
                onTextChanged: {
                    // 实时更新字符计数（限制36字符）
                    if (text.length > 36) {
                        text = text.substring(0, 36) // 截断超长文本
                    }
                    rightCounter.text = `${text.length}/36`
                }
                Component.onCompleted: {
                    rightCounter.text = "0/36" // 初始化计数
                }
            }

            // 右侧字符计数
            Text {
                id: rightCounter
                color: "gray"
                font.pixelSize: 14
                text: "0/36"
                Layout.preferredWidth: 100  // 固定宽度
            }
        }

        RowLayout {
            width: parent.width

            Item{
                width:60
            }

            // 标签（签名）
            Text {
                text: "签名:"
                color: "black"
                font.pixelSize: 16
                Layout.preferredWidth: 40
            }

            // 输入框
            TextField {
                id: signatureField
                placeholderText: "请输入签名"
                placeholderTextColor:"lightgrey"
                font.pixelSize: 16
                color: "black" // 文字颜色
                background: Rectangle {
                    border.color:"#A0A0A0"
                    color: "white"
                }
                Layout.fillWidth: true  // 填充剩余的宽度
                onTextChanged: {
                    // 实时更新字符计数（限制36字符）
                    if (text.length > 80) {
                        text = text.substring(0, 80) // 截断超长文本
                    }
                    rightCounter1.text = `${text.length}/80`
                }
                Component.onCompleted: {
                    rightCounter1.text = "0/80" // 初始化计数
                }
            }

            // 右侧字符计数
            Text {
                id: rightCounter1
                color: "gray"
                font.pixelSize: 14
                text: "0/80"
                Layout.preferredWidth: 100
            }
        }

        RowLayout {
            width: parent.width

            Item{
                width:60
            }

            // 标签（性别）
            Text {
                text: "性别:"
                color: "black"
                font.pixelSize: 16
                Layout.preferredWidth: 40
            }

            ComboBox{
                    id:genderCombo
                    Layout.preferredWidth: 186
                    model:["女","男","其他"]
                    currentIndex:0
                    font.pixelSize: 16
                }
            Item{
                Layout.fillWidth: true
            }


        }
        RowLayout {
            width: parent.width

            Item{
                width:60
            }

            // 标签（生日）
            Text {
                text: "生日:"
                color: "black"
                font.pixelSize: 16
                Layout.preferredWidth: 40
            }

            // 输入框
            TextField {
                id: ageField
                placeholderText: "请输入出生年月"
                placeholderTextColor:"lightgrey"
                font.pixelSize: 16
                color: "black" // 文字颜色
                background: Rectangle {
                    border.color:"#A0A0A0"
                    color: "white"
                }
                Layout.preferredWidth: 186
                onTextChanged: {
                    // 实时更新字符计数（限制36字符）
                    if (text.length > 80) {
                        text = text.substring(0, 80) // 截断超长文本
                    }
                    rightCounter.text = `${text.length}/80`
                }
                Component.onCompleted: {
                    rightCounter.text = "0/80" // 初始化计数
                }
            }
            Item{
                Layout.fillWidth: true
            }


        }
        RowLayout {
            width: parent.width

            Item{
                width:60
            }

            // 标签（地区）
            Text {
                text: "地区:"
                color: "black"
                font.pixelSize: 16
                Layout.preferredWidth: 40
            }

            ComboBox{
                    id:regionCombo
                    Layout.preferredWidth: 186
                    model:["中国重庆市","其他"]
                    currentIndex:0
                    font.pixelSize: 16


                }
            Item{
                Layout.fillWidth: true
            }
        }
    }
}
