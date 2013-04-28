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
            role: "connected"
            width: 10
            delegate: Item {
                anchors.fill: parent
                Rectangle{
                    anchors.centerIn: parent

                    width: 12
                    height: 12
                    radius: 10
                    color: itemValue ? "green" : "red"
                }

            }
        }
        TableViewColumn {
            role: "id"
            title: "ID"
            width: 120
        }
        TableViewColumn {
            role: "incomingBand"
            title: "Incoming Speed"
            width: 120
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,true)
                }
            }
        }
        TableViewColumn {
            role: "outgoingBand"
            title: "Outgoing Speed"
            width: 120
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,true)
                }
            }
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
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,false)
                }
            }
        }
        TableViewColumn {
            role: "outgoingTraffic"
            title: "Outgoing traffic"
            width: 120
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,false)
                }
            }
        }

        TableViewColumn {
            role: "transport"
            title: "Transport"
            width: 120
        }
    }

}
