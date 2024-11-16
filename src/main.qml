// EditorView.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1280
    height: 700
    title: "UwIDE"

    // A simple TextArea for text input
    TextArea {
        id: textEditor
        anchors.fill: parent
        wrapMode: TextArea.Wrap
        font.pixelSize: 14
        text: "Hello, Qt Quick!"  // Default text to show
    }
}
