import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import Cangote 1.0

Window {
    id: addPeerWnd

    width: 400
    height: 300

    color: "lightgrey"
    title: "Add new peer"
    TextArea{
        id: textArea
        width: parent.width
        height: parent.height -30
    }

    RowLayout{

        anchors.top: textArea.bottom
        anchors.right: textArea.right

        CheckBox{
            text: qsTr("Add as a friend")
        }

        Button{

            width: 60
            height: 30
            text:qsTr("Add")

            onClicked: {
                var text = textArea.text;
                Cangote.gnunet.network.putHello(text);
                addPeerWnd.close();
            }
        }
    }

}
