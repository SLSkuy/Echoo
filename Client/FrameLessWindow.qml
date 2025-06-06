import QtQuick

Window{
    id: window
    height: 450
    width: 320
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Window

    // 实现全局拖拽功能
    MouseArea{
        id: dragArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor

        onPressed:function() {
            cursorShape = Qt.ClosedHandCursor
            window.startSystemMove()
        }

        onReleased:{
            cursorShape = Qt.ArrowCursor
        }
    }
}
