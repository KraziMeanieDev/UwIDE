import QtQuick
import QtQuick.Controls.Fusion

// import QtQuick.Layouts

Rectangle {
    id: sidePanel
    radius: 8
    SplitView.minimumWidth: 200
    SplitView.maximumWidth: 300
    color: "#2b2b2b"

    Text {
        text: "Explorer Panel"
        anchors.centerIn: parent
        color: "#cfcfcf"
    }

    ListView {
        width: parent.width
        height: parent.height
        model: explorer.folderContents

        delegate: Item {
            width: ListView.view.width
            height: 30

            Rectangle {
                width: parent.width
                height: 30
                color: "#333333"
                radius: 5

                Text {
                    anchors.centerIn: parent
                    text: modelData
                    color: "#cfcfcf"
                }
            }
        }
    }
}
