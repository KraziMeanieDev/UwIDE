import QtQuick
import QtQuick.Controls.Fusion

Rectangle {
    id: editorPanel
    SplitView.fillHeight: true
    radius: 8
    color: "#202020"

    property int lineCount: textEdit.text.split('\n').length
    property int visibleStartLine: Math.floor(flick.contentY / lineHeight)
    property int visibleEndLine: Math.min(Math.ceil((flick.contentY + flick.height) / lineHeight), lineCount)
    property real lineHeight: textEdit.font.pixelSize + 4

    Timer {
        id: lineCountTimer
        interval: 150
        repeat: false
        onTriggered: {
            editorPanel.lineCount = textEdit.text.split('\n').length;
            lineNumbersCanvas.requestPaint();
            textEdit.updatesPending = false;
        }
    }

    Flickable {
        id: flick
        anchors.fill: parent
        contentWidth: textEdit.width + lineNumbersArea.width
        contentHeight: textEdit.contentHeight
        boundsBehavior: Flickable.StopAtBounds
        pixelAligned: true
        maximumFlickVelocity: 2500
        clip: true
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
            interactive: true
            minimumSize: 0.1
        }

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
            color: "#1a1a1a"  // Darker background for better contrast
            topLeftRadius: editorPanel.radius

            Canvas {
                id: lineNumbersCanvas
                anchors.fill: parent
                property real lastContentY: 0

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    ctx.font = textEdit.font.pixelSize + "px '" + textEdit.font.family + "'";
                    ctx.fillStyle = "#8f8f8f";  // Lighter text for better readability
                    ctx.textAlign = "right";

                    ctx.beginPath();
                    for (var i = editorPanel.visibleStartLine; i <= editorPanel.visibleEndLine; i++) {
                        var y = i * editorPanel.lineHeight;
                        ctx.fillText(i + 1, width - 4, y + textEdit.font.pixelSize);
                    }
                    ctx.fill();
                    lastContentY = flick.contentY;
                }

                Connections {
                    target: flick
                    function onContentYChanged() {
                        if (Math.abs(lineNumbersCanvas.lastContentY - flick.contentY) > editorPanel.lineHeight / 2) {
                            lineNumbersCanvas.requestPaint();
                        }
                    }
                }

                Connections {
                    target: textEdit
                    function onTextChanged() {
                        lineNumbersCanvas.requestPaint();
                    }
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

            // Rendering optimizations
            // renderType: Text.NativeRendering
            // antialiasing: true
            // layer.enabled: true
            // layer.smooth: true
            textFormat: TextEdit.PlainText

            // Memory optimizations
            persistentSelection: false
            selectByMouse: true
            mouseSelectionMode: TextEdit.SelectCharacters

            // Batch updates
            property bool updatesPending: false

            onTextChanged: {
                if (!updatesPending) {
                    updatesPending = true;
                    lineCountTimer.restart();
                }
            }

            onCursorRectangleChanged: {
                if (!flick.moving) {
                    flick.ensureVisible(cursorRectangle);
                }
            }
        }
    }
}
