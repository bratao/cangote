import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0

Item{

    id:shared
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
        id: sharedList
        anchors.fill: parent

        model:Cangote.models.sharedModel



        TableViewColumn {
            role: "filename"
            title: "Filename"
            width: 120
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
            }

            contextMenu.popup()
        }
    }

}
