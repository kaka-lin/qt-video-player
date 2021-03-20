import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.10
import QtGraphicalEffects 1.0 // DropShadow
import QtMultimedia 5.9

import components.common 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    //visibility: Window.FullScreen
    title: qsTr("The Example of OpenCV and QML")

    header: ToolBar {
        id: menu

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.color: "#999"

            gradient: Gradient {
                GradientStop { position: 0 ; color: "#fff" }
                GradientStop { position: 1 ; color: "#eee" }
            }
        }

        Clock {
            id: clock
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.verticalCenter: parent.verticalCenter

            gradient: Gradient {
                GradientStop { position: 0; color: "#fff" }
                GradientStop { position: 1; color: "#eee" }
            }
        }
    }

    Row {
        id: btnRow
        spacing: (parent.width - playBtn.width * 3) / 4

        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: playBtn;
            width: 120;
            height: 60;
            text: qsTr("Play")
            onClicked: {
                player.play();
            }
        }

        Button {
            id: pauseBtn;
            width: playBtn.width;
            height: playBtn.height;
            text: qsTr("Pause")
            onClicked: {
                player.pause();
            }
        }

        Button {
            id: stopBtn;
            width: playBtn.width;
            height: playBtn.height;
            text: qsTr("Stop")
            onClicked: {
                player.stop();
            }
        }
    }

    Rectangle {
        id: videoArea
        width: parent.width
        height: parent.height - 40

        anchors.top: btnRow.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        VideoOutput {
            source: player
            anchors.fill: parent
            focus : visible // to receive focus and capture key events when visible
        }
    }
}
