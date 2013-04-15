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
            browserBlock.selected = false
            networkBlock.selected = false
            searchBlock.selected = false
            transferBlock.selected = false
            sharedBlock.selected = false
            searchBlock.itemSelected = -1
            }


        Block
        {
            id: browserBlock
            title: "Browser"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 0;
                selected = true;
            }
        }
        Block
        {
            id: networkBlock
            title: "Network"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 1;
                selected = true;
            }
        }

        Block
        {
            id: searchBlock
            title: "Searches"
            model: Cangote.models.searchModel
            onHeaderClicked: {

            }
            onChanged: {
                browserBlock.selected = false
                networkBlock.selected = false
                searchBlock.selected = false
                transferBlock.selected = false
                sharedBlock.selected = false
                center.source = 2;
                center.search.visibleIndex = indexChanged
            }
        }

        Block
        {
            id: transferBlock
            title: "Transfer"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 3;
                selected = true;
            }
        }

        Block
        {
            id: sharedBlock
            title: "Shared Files"
            onHeaderClicked: {
                parent.resetSelected()
                center.source = 4;
                selected = true;
            }
        }



    }
}
