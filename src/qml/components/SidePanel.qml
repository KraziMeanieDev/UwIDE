import QtQuick
import QtQuick.Controls.Fusion

Rectangle {
    id: sidePanel
    radius: 8
    SplitView.minimumWidth: 200
    SplitView.maximumWidth: 300
    color: "#202020"

    Component.onCompleted: {
        console.log("TreeView initialized with model:", explorerModel);
    }

    Rectangle {
        id: sidePanelHeader
        height: 40
        width: parent.width
        color: "#202020"
        topLeftRadius: parent.radius
        topRightRadius: parent.radius
        z: 2

        Text {
            text: "Explorer"
            font.bold: true
            color: "#cfcfcf"
            font.pointSize: 10
            anchors.verticalCenter: parent.verticalCenter
            leftPadding: 15
        }
    }

    Rectangle {
        id: sidePanelSeparator
        anchors.top: sidePanelHeader.bottom
        width: parent.width
        height: 2
        color: "#323232"
    }

    TreeView {
        id: fileSystemView
        anchors.top: sidePanelSeparator.bottom
        width: parent.width
        height: parent.height - sidePanelHeader.height
        clip: true
        model: explorerModel
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
            stepSize: 20
            width: 8
            background: Rectangle {
                color: "transparent" // Conditional background color
                radius: 8
            }
        }

        delegate: Rectangle {
            id: treeDelegate
            required property bool expanded
            required property int hasChildren
            required property int depth
            required property var model

            implicitWidth: fileSystemView.width
            implicitHeight: 30
            color: mouse.hovered ? "#303030" : "transparent"

            HoverHandler {
                id: mouse
                acceptedDevices: PointerDevice.Mouse
                cursorShape: Qt.PointingHandCursor
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("Item clicked:", model.path);
                    if (model.isDirectory) {
                        console.log(model.name + " is a directory");
                    } else {
                        codeDocumentModel.loadDocumentChunk(model.path, 0, 1000);
                    }
                    // if (hasChildren) {
                    //     fileSystemView.toggleExpanded(row);
                    // }
                }
            }

            Row {
                spacing: 4
                x: depth * 12
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    text: hasChildren ? (expanded ? "▼" : "▶") : ""
                    color: "#cfcfcf"
                    font.pointSize: 8
                    visible: hasChildren
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    text: model ? model.name : ""
                    color: "#cfcfcf"
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 15
                }
            }
        }
    }
}

// Connections {
//     target: explorerModel
//     function onRootPathChanged() {
//         console.log("Root path changed in TreeView");
//         fileSystemView.forceLayout();
//     }
// }
