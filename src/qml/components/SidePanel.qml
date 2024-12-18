import QtQuick
import QtQuick.Controls.Fusion

// import QtQuick.Layouts

Rectangle {
    id: sidePanel
    radius: 8
    SplitView.minimumWidth: 200
    SplitView.maximumWidth: 300
    color: "#2b2b2b"

    Rectangle {
        id: sidePanelHeader
        height: 40
        width: parent.width
        color: "#2b2b2b"
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

    ListView {
        id: list
        anchors.top: sidePanelSeparator.bottom
        width: parent.width
        height: parent.height - sidePanelHeader.height
        model: explorer.folderContents
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

        populate: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 200
            }
        }

        delegate: Item {
            width: ListView.view.width
            height: 30

            Rectangle {
                width: parent.width
                height: 30
                color: mouse.hovered ? "#333333" : "transparent"
                // topLeftRadius: (index === 0) ? sidePanel.radius : 0
                // topRightRadius: (index === 0) ? sidePanel.radius : 0
                bottomRightRadius: (index === explorer.folderContents.length - 1) ? sidePanel.radius : 0
                bottomLeftRadius: (index === explorer.folderContents.length - 1) ? sidePanel.radius : 0

                HoverHandler {
                    id: mouse
                    acceptedDevices: PointerDevice.Mouse
                    cursorShape: Qt.PointingHandCursor
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        // Log the path of the clicked item (using modelData)
                        console.log("Item clicked:", modelData.path);
                    }
                }

                Text {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: modelData.name
                    color: "#cfcfcf"
                    leftPadding: 15
                }
            }
        }
    }
}
