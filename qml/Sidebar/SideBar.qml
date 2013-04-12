import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

import "../"
Rectangle {
    color: "#474747"

    Column
    {
        anchors.fill: parent
        /*
        SideBarBlock
        {
            id: searchBlock
            title: "search"
            anchors.right : parent.right
            anchors.left : parent.left
            height: parent.height/2
        }*/
        Block
        {
            id: searchBlock
            title: "Searches"
            anchors.right : parent.right
            anchors.left : parent.left
            height: parent.height///2
        }

    }
}
