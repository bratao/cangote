import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

Item {
    property string searchTerm
    property var searchModel

    //Tooltip support.
    property bool needTooltip: false
    property real tooltipX: 0
    property real tooltipY: 0
    property int tooltipIndex: -1
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
        x: tooltipX
        y: tooltipY
        states: [
            State {
                name: "inuse"
                when: needTooltip
                PropertyChanges {
                    target: tooltip
                    visible: true
                    opacity:0.7

                }
            },
            State {
                name: "notinuse"
                when: !needTooltip
                PropertyChanges {
                    target: tooltip
                    visible: false
                    opacity:0.0
                }
            }
        ]

            transitions: Transition {
                to: "inuse"
                PropertyAnimation {target: tooltip; property: "opacity"; duration: 2000; easing.type: Easing.InCirc }

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
                    console.log("TODO: Double clicked.")
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
                            anchors.verticalCenter: parent.verticalCenter
                            color: styleData.textColor
                            elide: styleData.elideMode
                            text: Utils.friendlyUnit(styleData.value,false)
                            renderType: Text.NativeRendering
                        }
                    }
                }

            }
            MouseArea {
                id: ma
                anchors.fill: searchResultList
                hoverEnabled: true
                acceptedButtons: Qt.RightButton

                onMouseXChanged: {
                    var index = searchResultList.rowAt(mouse.x, mouse.y)
                    if (index !== -1){
                        if(index !== tooltipIndex )
                        {
                           tooltipIndex = index
                           needTooltip = false
                        }

                        tooltipX= ma.mapToItem(resultPage,mouseX,0).x
                        tooltipY= ma.mapToItem(resultPage,0,mouseY).y
                        tooltip.searchTerm = index
                        needTooltip = ma.containsMouse

                    }
                    else
                    {
                        needTooltip = false
                    }
                }

                onHoveredChanged: {
                    needTooltip= ma.containsMouse
                }


                onClicked: {

                    var index = searchResultList.rowAt(mouse.x, mouse.y)
                    if (index !== -1){


                        searchResultList.forceActiveFocus()
                        searchResultList.currentRow = index
                    }

                    contextMenu.popup()
                }
            }

    }
