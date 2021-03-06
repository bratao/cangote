import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

import "../"
Rectangle {
    color: "#474747"

    Column
    {
        anchors.fill: parent

        function resetSelected() {
            //browserBlock.selected = false
            networkBlock.selected = false
            searchBlock.selected = false
            transferBlock.selected = false
            sharedBlock.selected = false
            searchBlock.itemSelected = -1
            }

/*
        Block
        {
            id: browserBlock
            title: "Browser"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 0;
                selected = true;
            }
        }*/
        Block
        {
            id: networkBlock
            title: "Network"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 0;
                selected = true;
            }
        }

        Block
        {
            id: searchBlock
            title: "Search"
            model: Cangote.models.searchModel
            onHeaderClicked: {
                header.searchField.text = ""
                header.searchField.focus = true

            }
            onChanged: {
                //browserBlock.selected = false
                networkBlock.selected = false
                searchBlock.selected = false
                transferBlock.selected = false
                sharedBlock.selected = false
                center.source = 1;
                center.search.visibleIndex = indexChanged
            }
        }

        Block
        {
            id: transferBlock
            title: "Transfer"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 2;
                selected = true;
            }
        }

        Block
        {
            id: sharedBlock
            title: "Shared Files"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 3;
                selected = true;
            }
        }



    }
}
