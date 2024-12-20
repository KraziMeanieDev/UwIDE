pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Fusion 2.15
import QtQuick.Dialogs
import QtQuick.Window
import "./qml/components"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Uwide")
    color: "#181818"

    Component.onCompleted: {
        opacityAnimation.start();
    }

    PropertyAnimation {
        id: opacityAnimation
        target: mainWindow
        property: "opacity"
        from: 0
        to: 1
        duration: 200
    }

    menuBar: MenuBar {}

    FolderDialog {
        id: folderDialog
        title: "Open Folder"
        currentFolder: ""
        onAccepted: {
            console.log("Selected folder:", folderDialog.selectedFolder);
            explorer.browseFolder(folderDialog.selectedFolder);
            for (var i = 0; i < explorer.folderContents.length; i++) {
                var folder = explorer.folderContents[i];
                console.log("Item " + i + ": Name: " + folder.name + ", Path: " + folder.path);
            }
        }
    }

    SplitView {
        anchors.margins: 5
        anchors.topMargin: 0
        anchors.fill: parent
        clip: true
        handle: Rectangle {
            implicitWidth: 5
            color: SplitHandle.hovered ? "#c5897d" : "#181818"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SizeHorCursor
            }
            Behavior on color {
                ColorAnimation {
                    duration: 500
                    easing.type: Easing.Linear
                }
            }
        }

        SidePanel {}

        SplitView {
            orientation: Qt.Vertical

            handle: Rectangle {
                implicitHeight: 5
                color: SplitHandle.hovered ? "#c5897d" : "#181818"
                Behavior on color {
                    ColorAnimation {
                        duration: 500
                        easing.type: Easing.Linear
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.SizeVerCursor
                }
            }

            EditorPanel {}

            Rectangle {
                id: terminal
                SplitView.minimumHeight: 200
                SplitView.maximumHeight: 300
                radius: 7
                color: "#202020"
                // This is where you would embed your QScintilla or other editor component
                Text {
                    text: "Terminal Area"
                    anchors.centerIn: parent
                    color: "#cfcfcf"
                }
            }
        }
    }

    // Text {
    //     anchors.centerIn: parent
    //     text: "Hello, World"
    //     font.pointSize: 50
    //     font.family: "JetBrains Mono"
    // }
}
