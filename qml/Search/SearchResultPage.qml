import QtQuick 2.0
import QtQuick.Controls 1.0


Item {
    property string searchTerm
    property var searchModel

    anchors.fill: parent

    Action {
        id: download
        text: "Download"
        onTriggered: console.log("TODO: Download transfer.")
    }


    Menu {
        id: contextMenu
        MenuItem { action: download }

    }


    TableView
    {
        id: searchResultList
        anchors.fill: parent
        model: searchModel

        onActivated:
        {
            model.getResult(currentRow).download()
            //result.download()
            console.log("TODO: Double clicked.")
        }

        itemDelegate: Item {


            MouseArea {
                anchors.fill:  parent
                acceptedButtons:  Qt.RightButton
                propagateComposedEvents: true

                onPressed: {

                    contextMenu.popup(mouseX,mouseY,0, parent)
                    searchResultList.currentRow = rowIndex

                }
            }
            Text {
                anchors.fill:  parent
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
                text: itemValue
            }
        }



        TableViewColumn
        {
            title: "Name"
            role: "filename"
        }

        TableViewColumn
        {
            title: "Size"
            role: "filesize"
        }

    }

}
