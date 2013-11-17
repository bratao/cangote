import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Cangote 1.0
//import Utils 1.0

Item
{
    anchors.fill: parent
    id: transfersPage

    property var selectedFile: null


    Action {
        id: resume
        text: "Resume"
        onTriggered: console.log("TODO: Resume the transfer.")
    }

    Action {
        id: stop
        text: "Stop"
        onTriggered:
        {
            transfersList.name.visible = false;
            console.log("TODO: Stop the transfer.")
        }

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
            Utils.openFile(selectedFile.path);
        }
    }

    Action {
        id: openFolder
        text: "Open Folder"
        onTriggered: Utils.openFolder(selectedFile.path);
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


        TableViewColumn{
            id: name
            title: "Name"
            role: "name"
            delegate:Item{

                Image{
                    id: fileType
                    width: 16
                    height: 16
                    source: "image://downloadsThumbnail/" + styleData.row
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: fileType.right
                    anchors.right: parent.right

                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: styleData.value
                    renderType: Text.NativeRendering
                }
            }

        }

        TableViewColumn{
            title: "Size"
            role: "size"
            width: 60

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
        TableViewColumn{
            title: "Progress"
            role: "downloadProgress"
            delegate : Item{
                anchors.fill: parent

                ProgressBar{
                    anchors.fill: parent
                    minimumValue: 0
                    maximumValue: 100
                    value: styleData.value
                }
            }
        }
        TableViewColumn{
            title: "Status"
            role: "status"
            width: 80
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
            width: 100
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
        TableViewColumn{
            title: "Amount left"
            role: "amoutLeft"
            width: 100
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
        TableViewColumn{
            title: "Time Elapsed"
            role: "timeElapsed"
        }
    }
    MouseArea {
        anchors.fill: transfersList
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        onClicked: {

            var index = transfersList.rowAt(mouse.x, mouse.y)

            if (index !== -1){
                transfersList.forceActiveFocus()
                transfersList.selection.clear()
                transfersList.selection.select(index)
                selectedFile = Cangote.models.downloadsModel.get(index)
            }

            contextMenu.popup()
        }
    }


}

