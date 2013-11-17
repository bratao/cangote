import QtQuick 2.1
import QtQuick.Controls 1.1
//import QtQuick.Controls.Private 1.0

import Cangote 1.0

Item {
    property string searchTerm
    property var searchResultModel

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
        onTriggered: {
            searchResultModel.getResult(searchResultList.currentRow).download()
            console.log("TODO: Download transfer.")
        }
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
                    opacity:0.8

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
            PropertyAnimation {target: tooltip; property: "opacity"; duration: 200; easing.type: Easing.InExpo }

        }
    }


    TableView
    {
        id: searchResultList
        anchors.fill: parent
        model: searchResultModel
        sortIndicatorVisible: true
        SystemPalette{ id: syspal }

        onDoubleClicked:
        {
            searchResultModel.getResult(currentRow).download()
        }

        rowDelegate: Rectangle {
            /*! The background color. */
            property color backgroundColor: parent.backgroundVisible ? syspal.base : "transparent"

            /*! The alternate background color. */
            property color alternateBackgroundColor: Qt.darker(syspal.base, 1.06)

            height: 40
            property color selectedColor: styleData.hasActiveFocus ? "#38d" : "#999"
            gradient: Gradient {
                GradientStop {
                    color: styleData.selected ? Qt.lighter(selectedColor, 1.3) :
                                                styleData.alternate ? alternateBackgroundColor : backgroundColor
                    position: 0
                }
                GradientStop {
                    color: styleData.selected ? Qt.lighter(selectedColor, 1.0) :
                                                styleData.alternate ? alternateBackgroundColor : backgroundColor
                    position: 1
                }
            }
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: styleData.selected ? Qt.darker(selectedColor, 1.4) : "transparent"
            }
            Rectangle {
                anchors.top: parent.top
                width: parent.width ; height: 1
                color: styleData.selected ? Qt.darker(selectedColor, 1.1) : "transparent"
            }
        }




        TableViewColumn
        {
            title: "Preview"
            role: "preview"
            width: 66
            resizable:false
            delegate:Item{


                Image {
                    id: thumbnail
                    width: 62; height: 35
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    clip: true
                    source: styleData.value
                    anchors.centerIn: parent
                }

                Image {
                    id: fileType
                    width: 20; height: 20
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    clip: true
                    source: styleData.value + "/thumbnail"

                    //anchors.centerIn: parent
                }


            }

        }

        TableViewColumn
        {
            title: "Name"
            role: "filename"
            width: 400
            delegate:Item{
                Text {

                    anchors.fill : parent
                    verticalAlignment: Qt.AlignVCenter
                    color: styleData.textColor
                    elide: styleData.elideMode
                    text: styleData.value
                    renderType: Text.NativeRendering
                    wrapMode: TextEdit.WordWrap
                }
            }
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
                tooltip.metadata = searchResultModel.getResult(index)
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
