import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0
//import Utils 1.0

Item
{
    anchors.fill: parent
    id: transfersPage



    Action {
        id: resume
        text: "Resume"
        onTriggered: console.log("TODO: Resume the transfer.")
    }

    Action {
        id: stop
        text: "Stop"
        onTriggered: console.log("TODO: Stop the transfer.")
    }

    Action {
        id: cancel
        text: "Cancel"
        onTriggered: console.log("TODO: Cancel the transfer.")
    }

    Action {
        id: openFile
        text: "Open File"
        onTriggered: {
            Utils.openFilePicker();
        }
    }

    Action {
        id: openFolder
        text: "Open Folder"
        onTriggered: console.log("TODO: Open the transfer folder.")
    }



    Menu {
        id: contextMenu
        MenuItem { action: resume }
        MenuItem { action: stop }
        MenuItem { action: cancel }
        MenuSeparator { }
        MenuItem { action: openFile }
        MenuItem { action: openFolder }

    }



    TableView
    {
        id: transfersList
        anchors.fill: parent
        model:Cangote.models.downloadsModel


        itemDelegate: Item {

            MouseArea {
                anchors.fill:  parent
                acceptedButtons: Qt.RightButton
                onPressed: {
                    contextMenu.popup(mouseX,mouseY,0, parent)
                    transfersList.currentRow = rowIndex
                }
            }
            Text {
                anchors.fill:  parent
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
                text: itemValue
             }
         }








        TableViewColumn{
            title: "Name"
            role: "name"
        }

        TableViewColumn{
            title: "Size"
            role: "size"
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,false)
                }
            }
        }
        TableViewColumn{
            title: "Progress"
            role: "downloadProgress"
            delegate : Item{
                anchors.fill: parent

                ProgressBar{
                    anchors.fill: parent
                    minimumValue: 0
                    maximumValue: 100
                    value: itemValue
                }
            }
        }
        TableViewColumn{
            title: "Status"
            role: "status"
        }
        TableViewColumn{
            title: "Down Speed"
            role: "downSpeed"

        }
        TableViewColumn{
            title: "ETA"
            role: "era"
        }
        TableViewColumn{
            title: "Label"
            role: "label"
        }
        TableViewColumn{
            title: "Add Date"
            role: "addDate"
        }
        TableViewColumn{
            title: "Amount Downloaded"
            role: "amountDownloaded"
        }
        TableViewColumn{
            title: "Amount left"
            role: "amoutLeft"
        }
        TableViewColumn{
            title: "Time Elapsed"
            role: "timeElapsed"
        }
    }


}

