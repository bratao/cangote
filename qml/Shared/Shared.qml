import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0

Item{

    id:shared
    anchors.fill: parent


    TableView
    {
        //anchors.fill: parent
        id: list
        anchors.fill: parent

        model:Cangote.models.sharedModel



        TableViewColumn {
            role: "filename"
            title: "Filename"
            width: 120
        }

    }

}
