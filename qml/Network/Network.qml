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
        id: networkTable
        anchors.fill: parent

        model:Cangote.models.networkModel


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
                    color: styleData.value ? "green" : "red"
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
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: Utils.friendlyUnit(styleData.value,true)
                    renderType: Text.NativeRendering
                }
            }
        }
        TableViewColumn {
            role: "outgoingBand"
            title: "Outgoing Speed"
            width: 120
            delegate:Item{
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: Utils.friendlyUnit(styleData.value,true)
                    renderType: Text.NativeRendering
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
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: Utils.friendlyUnit(styleData.value,false)
                    renderType: Text.NativeRendering
                }
            }
        }
        TableViewColumn {
            role: "outgoingTraffic"
            title: "Outgoing traffic"
            width: 120
            delegate:Item{
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: Utils.friendlyUnit(styleData.value,false)
                    renderType: Text.NativeRendering
                }
            }
        }

        TableViewColumn {
            role: "transport"
            title: "Transport"
            width: 120
        }
    }

    MouseArea {
        anchors.fill: networkTable
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        onClicked: {

            var index = networkTable.rowAt(mouse.x, mouse.y)
            if (index !== -1){
                networkTable.forceActiveFocus()
                networkTable.currentRow = index
            }

            contextMenu.popup()
        }
    }

}
