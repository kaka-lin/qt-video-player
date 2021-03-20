import QtQuick 2.10
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

ToolButton {
    id: root

    property real margin: 2
    property string grad_color_1: "#fff"
    property string grad_color_2: "#eee"
    property string iconSource: "qrc:/images/homepage.png"
    property real _height: 0
    property real _width: 0
    signal btnClicked()

    height: root._height ? root._height : ToolButton.height
    width: root._width ? root._width : ToolButton.width
    
    Rectangle {
        id: btnBackground
        width: root.width
        height: root.height - margin

        anchors.top: root.top
        anchors.bottom: root.bottom
        anchors.topMargin: root.margin / 2
        anchors.bottomMargin: root.margin / 2

        gradient: Gradient {
            id: grad
            GradientStop { position: 0 ; color: root.grad_color_1 }
            GradientStop { position: 1 ; color: root.grad_color_2 }
        }
    }

    Image {
        id: icon
        source: root.iconSource
        asynchronous:true
        fillMode: Image.PreserveAspectFit 
        anchors.fill: parent
    }

    DropShadow {
        anchors.fill: icon
        horizontalOffset: 2
        verticalOffset: 2
        samples: 17
        color: "#80000000"
        source: icon
    }

    onClicked: {
        if (btnBackground.gradient != null) {

            btnBackground.gradient = null;
        }
        btnBackground.gradient = grad;

        root.btnClicked();
    }

    onPressed: {
        btnBackground.gradient = null;
        btnBackground.color = "#a9a9a9";  
    }
}
