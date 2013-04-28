import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0

import Cangote 1.0

Window {
    id: addPeerWnd

    width: 400
    height: 300

    color: "lightgrey"
    title: "Preferences"
    TextArea{
        id: textArea
        width: parent.width
        height: parent.height -30
    }
    Button{
        anchors.top: textArea.bottom
        anchors.right: textArea.right
        width: 60
        height: 30
        text:qsTr("Add")
    }

}
