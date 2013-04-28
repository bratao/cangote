import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0

Rectangle {
    height: 20
    color : "lightgrey"


    Row{
        anchors.verticalCenter: parent.verticalCenter
        Rectangle{
            height: 15
            width: 15
            radius: 20
            color: Cangote.connected ? "green": "red"
        }

        Text{
            text: qsTr("Connected to: ") + Cangote.connectedPeers + qsTr(" peers")
        }
    }

}
