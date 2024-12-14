import QtQuick
import QtQuick.Controls.Fusion

// import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Uwide")
    color: "peachpuff"

    Text {
        anchors.centerIn: parent
        text: "Hello world"
        font.pointSize: 16
        font.bold: true
    }

    // RowLayout {
    //     // Main layout: Sidebar on the left, editor/terminal on the right
    //     anchors.fill: parent
    //     spacing: 0 // No spacing between sidebar and editor area

    //     // 1. Sidebar (Left)
    //     Rectangle {
    //         id: sidebar
    //         Layout.minimumWidth: 200
    //         Layout.maximumWidth: 300 // Optional maximum width
    //         Layout.fillHeight: true
    //         color: "#f0f0f0" // Light gray background
    //         // Add your sidebar content here (e.g., ListView, TreeView)
    //         Text {
    //             text: "File Explorer"
    //             anchors.centerIn: parent
    //         }
    //     }

    //     // 2. Editor and Terminal (Right)
    //     ColumnLayout {
    //         Layout.fillWidth: true
    //         Layout.fillHeight: true
    //         spacing: 5

    //         // 2.1 Editor Panel (Top)
    //         Rectangle {
    //             id: editorPanel
    //             Layout.fillWidth: true
    //             Layout.fillHeight: true // Editor takes up most of the space
    //             color: "white"
    //             // This is where you would embed your QScintilla or other editor component
    //             Text {
    //                 text: "Editor Area"
    //                 anchors.centerIn: parent
    //             }
    //         }

    //         // 2.2 Terminal (Bottom)
    //         Rectangle {
    //             id: terminal
    //             Layout.fillWidth: true
    //             Layout.preferredHeight: 200 // Fixed height for the terminal
    //             color: "#282c34" // Dark background for the terminal
    //             // Add your terminal component here
    //             Text {
    //                 text: "Terminal"
    //                 anchors.centerIn: parent
    //                 color: "white"
    //             }
    //         }
    //     }
    // }
}
