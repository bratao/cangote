import QtQuick 2.0

Rectangle {

    property string text: "Set text"

    signal clicked

    width: parent.width
    height: 20

    Text{
        text: parent.text
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            parent.clicked()
        }

    }

}
