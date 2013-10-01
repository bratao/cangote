import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0

Item{

    id:shared
    anchors.fill: parent
    property var selectedFile: null

    Action {
        id: copyLink
        text: "Copy Link"
        onTriggered: console.log("TODO: Copy link.")
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
        MenuItem { action: copyLink }
        MenuItem { action: openFile }
        MenuItem { action: openFolder }

    }


    TableView
    {
        //anchors.fill: parent
        id: sharedList
        anchors.fill: parent

        model:Cangote.models.sharedModel



        TableViewColumn {
            role: "name"
            title: "File Name"
            width: 350
        }
        TableViewColumn {
            role: "size"
            title: "Size"
            delegate:Item{
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: Utils.friendlyUnit(styleData.value,false)
                    renderType: Text.NativeRendering
                }
            }
            width: 80
        }
        TableViewColumn {
            role: "status"
            title: "Status"
            width: 100
        }
        TableViewColumn {
            role: "path"
            title: "Full Path"
            width: 350
        }

    }
    MouseArea {
        anchors.fill: sharedList
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        onClicked: {

            var index = sharedList.rowAt(mouse.x, mouse.y)
            if (index !== -1){
                sharedList.forceActiveFocus()
                sharedList.currentRow = index
                selectedFile = Cangote.models.sharedModel.get(index)
            }

            contextMenu.popup()
        }
    }

}
