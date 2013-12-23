import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0

Item {
    anchors.fill: parent

    RowLayout{
        anchors.fill: parent
        Image {
            id: image
            source: "Mascote.png"
            width: 200
            height: 300
            Layout.maximumWidth: 200
            Layout.maximumHeight: 300
            fillMode: Image.PreserveAspectFit

        }

        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: name
            text: qsTr("Sou w1elcome")
        }
    }
}
