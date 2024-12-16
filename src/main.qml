pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Fusion
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
    color: "#202020"

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

    SplitView {
        anchors.margins: 5
        anchors.topMargin: 0
        anchors.fill: parent
        handle: Rectangle {
            implicitWidth: 5
            color: SplitHandle.hovered ? "#c5897d" : "transparent"
            Behavior on color {
                ColorAnimation {
                    duration: 500
                    easing.type: Easing.Linear
                }
            }
        }

        SidePanel {
            Text {
                text: "Explorer Panel"
                anchors.centerIn: parent
                color: "#cfcfcf"
            }
        }

        SplitView {
            orientation: Qt.Vertical

            handle: Rectangle {
                implicitHeight: 5
                color: SplitHandle.hovered ? "#c5897d" : "transparent"
                Behavior on color {
                    ColorAnimation {
                        duration: 500
                        easing.type: Easing.Linear
                    }
                }
            }

            Rectangle {
                id: editorPanel
                SplitView.fillHeight: true
                radius: 8
                color: "#2b2b2b"
                // This is where you would embed your QScintilla or other editor component
                Text {
                    text: "Editor Area"
                    anchors.centerIn: parent
                    color: "#cfcfcf"
                }
            }

            Rectangle {
                id: terminal
                SplitView.minimumHeight: 200
                SplitView.maximumHeight: 300
                radius: 7
                color: "#2b2b2b"
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
