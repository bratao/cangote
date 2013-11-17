import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import Cangote 1.0

Window {
    id: myInfoWnd

    width: 400
    height: 300

    color: "lightgrey"
    title: "My Info"
    ColumnLayout{

        anchors.fill: parent

        Label{
            text: "Share this link to your friends :"
            height: 20
        }


        TextArea{
            id: textArea
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button{

            anchors.right: parent.right
            width: 60
            height: 40
            text:qsTr("Copy to Clipboard")

            onClicked: {
                textArea.selectAll();
                textArea.copy();
            }
        }

    }

}
