import QtQuick
import QtQuick.Controls.Fusion

MenuBar {
    id: menuBar
    padding: 5
    spacing: 10
    background: Rectangle {
        color: "#181818"
    }

    delegate: MenuBarItem {
        id: menuBarItem
        font.pointSize: 10
        leftPadding: 15  // More padding on the left of the menu title
        rightPadding: 15  // More padding on the right of the menu title

        contentItem: Text {
            text: menuBarItem.text
            font: menuBarItem.font
            color: menuBarItem.highlighted ? "#ffffff" : "#cfcfcf"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            radius: 4
            anchors.margins: 10
            opacity: enabled ? 1 : 0.3
            color: menuBarItem.highlighted ? "#2a2a2a" : "transparent"

            // Behavior on color {
            //     ColorAnimation {
            //         duration: 100
            //     }
            // }
        }
    }
    Menu {
        title: qsTr("File")
        Action {
            text: qsTr("&New...")
        }
        Action {
            text: qsTr("&Open...")
            icon.name: "document-open"
        }
        Action {
            text: qsTr("&Open Folder...")
            onTriggered: {
                folderDialog.open();
            }
        }
        Action {
            text: qsTr("&Save")
        }
        Action {
            text: qsTr("Save &As...")
        }
        MenuSeparator {}
        Action {
            text: qsTr("Quit")
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: qsTr("Edit")
        Action {
            text: qsTr("Cu&t")
        }
        Action {
            text: qsTr("&Copy")
        }
        Action {
            text: qsTr("&Paste")
        }
    }
    Menu {
        title: qsTr("Help")
        Action {
            text: qsTr("&About")
        }
    }
}
