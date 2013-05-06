import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

Item {
    property string searchTerm
    property var searchModel
    property bool needTooltip: false
    property real tooltipX: 0
    property real tooltipY: 0
    anchors.fill: parent

    id: resultPage

    Action {
        id: download
        text: "Download"
        onTriggered: console.log("TODO: Download transfer.")
    }


    Menu {
        id: contextMenu
        MenuItem { action: download }

    }

    //The tooltip
    Tooltip {
        id: tooltip
        states: State {
            name: "inuse"
            when: needTooltip
            PropertyChanges {
                target: tooltip
                visible: true
                x: tooltipX
                y: tooltipY
            }
        }
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
            id: item

            MouseArea {
                id: ma
                anchors.fill:  parent
                acceptedButtons:  Qt.RightButton
                propagateComposedEvents: true
                hoverEnabled: true

                onMouseXChanged: {
                    tooltipX= ma.mapToItem(resultPage,mouseX,0).x
                    tooltipY= ma.mapToItem(resultPage,0,mouseY).y
                }

                onHoveredChanged: {
                    needTooltip=ma.containsMouse
                    tooltipX= ma.mapToItem(resultPage,mouseX,0).x
                    tooltipY= ma.mapToItem(resultPage,0,mouseY).y
                    tooltip.searchTerm = itemValue
                }

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
            delegate:Item{
                Text {
                    text: Utils.friendlyUnit(itemValue,false)
                }
            }
        }

    }

}
