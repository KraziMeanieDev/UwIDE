import QtQuick
import QtQuick.Controls.Fusion

Rectangle {
    id: editorPanel
    SplitView.fillHeight: true
    radius: 8
    color: "#2b2b2b"

    // Add property to cache line count
    property int lineCount: textEdit.text.split('\n').length

    Flickable {
        id: flick
        anchors.fill: parent
        contentWidth: textEdit.width + lineNumbersArea.width
        contentHeight: textEdit.contentHeight
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        ScrollBar.vertical: ScrollBar {}

        function ensureVisible(r) {
            if (flick.contentX >= r.x)
                flick.contentX = r.x;
            else if (flick.contentX + width <= r.x + r.width)
                flick.contentX = r.x + r.width - width;
            if (flick.contentY >= r.y)
                flick.contentY = r.y;
            else if (flick.contentY + height <= r.y + r.height)
                flick.contentY = r.y + r.height - height;
        }

        Rectangle {
            id: lineNumbersArea
            width: 40
            height: flick.contentHeight
            color: "#232323"

            Repeater {
                model: editorPanel.lineCount
                delegate: Text {
                    y: index * (textEdit.font.pixelSize + 4)
                    height: textEdit.font.pixelSize + 4
                    width: lineNumbersArea.width
                    text: index + 1
                    color: "#707070"
                    horizontalAlignment: Text.AlignRight
                    rightPadding: 4
                    font.family: textEdit.font.family
                    font.pixelSize: textEdit.font.pixelSize
                }
            }
        }

        TextEdit {
            id: textEdit
            x: lineNumbersArea.width
            width: flick.width - lineNumbersArea.width
            height: contentHeight
            font.pointSize: 12
            font.family: "JetBrains Mono"
            color: "#cfcfcf"
            text: codeDocumentModel.codeDocument
            wrapMode: TextEdit.NoWrap
            clip: true

            onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
            onTextChanged: editorPanel.lineCount = text.split('\n').length
        }
    }
}
