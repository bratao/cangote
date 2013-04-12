import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0

Item{

    id:network
    anchors.fill: parent

    Action {
        id: copyLink
        text: "Copy Link"
        onTriggered: console.log("TODO: Copy link.")
    }

    Menu {
        id: contextMenu
        MenuItem { action: copyLink }

    }


    TableView
    {
        //anchors.fill: parent
        id: list
        anchors.fill: parent

        model:Cangote.models.networkModel


        itemDelegate: Item {

            MouseArea {
                anchors.fill:  parent
                acceptedButtons: Qt.RightButton
                onPressed: {
                    contextMenu.popup(mouseX,mouseY,0, parent)
                    list.currentRow = rowIndex
                }
            }
            Text {
                anchors.fill:  parent
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
                text: itemValue
             }
         }

        TableViewColumn {
            role: "id"
            title: "ID"
            width: 120
        }
        TableViewColumn {
            role: "incomingBand"
            title: "Incoming Quota"
            width: 120
        }
        TableViewColumn {
            role: "outgoingBand"
            title: "Outgoing quota"
            width: 120
        }
        TableViewColumn {
            role: "hostname"
            title: "Hostname"
            width: 120
        }
        TableViewColumn {
            role: "incomingTraffic"
            title: "Incoming traffic"
            width: 120
        }
        TableViewColumn {
            role: "outgoingTraffic"
            title: "Outgoing traffic"
            width: 120
        }
        TableViewColumn {
            role: "connected"
            title: "Connected"
            width: 120
        }
        TableViewColumn {
            role: "transport"
            title: "Transport"
            width: 120
        }
    }

}
