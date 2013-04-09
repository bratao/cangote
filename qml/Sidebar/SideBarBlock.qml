import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

import "../"
Rectangle {
    property string title

    color: "#474747"


    Label{
        id: titleLabel
        text:title
        font.pixelSize: 15
        color: "grey"
        height: 20
    }

    TableView {
        id: tableView
        anchors.fill: parent
        anchors.topMargin: titleLabel.height

        frameVisible: false
        headerVisible: false
        //alternateRowColor: false
        backgroundColor: "transparent"
        Component.onCompleted:  {
            verticalScrollBar.anchors.topMargin = -8
            horizontalScrollBar.visible = false
        }

        verticalScrollBar.visible: false
        //verticalScrollBar.style: CustomScrollBarStyle { }

        TableViewColumn{ role: "term" ; width: 200 }

        model: Cangote.models.searchModel

        rowDelegate: BorderImage {
            id: rowBackground
            border.top: 1
            height: 20
            states: [
                State {
                    name: "normal"
                    when: !itemSelected
                    PropertyChanges { target: rowBackground; source: "" }
                },
                State {
                    name: "selectedActiveFocus"
                    when: itemSelected && tableView.activeFocus
                    PropertyChanges { target: rowBackground; source: "images/itemlistselectedfocus.png" }
                },
                State {
                    name: "selectedNoFocus"
                    when: itemSelected && !tableView.activeFocus
                    PropertyChanges { target: rowBackground; source: "images/itemlistselected.png" }
                }
            ]
        }

        itemDelegate: Item {
            width: tableView.verticalScrollBar.visible ? tableView.width - tableView.verticalScrollBar.width : tableView.width



            Image {
                id: playlistImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 15
                source: "images/playlist"+ (itemSelected && tableView.activeFocus ? "-activefocus" : "")
                        + ".png"
            }



            Text {
                id: playlistText
                anchors.top: parent.top
                anchors.topMargin: 1
                anchors.bottom: parent.bottom
                anchors.left: playlistImage.right
                anchors.leftMargin: 5
                anchors.right: closeButton.left
                //anchors.rightMargin: closeButton.source.length ? 5 : 0
                verticalAlignment: Text.AlignVCenter
                text: itemValue
                elide: Text.ElideRight
                style: Text.Raised
                font.pixelSize: 11
                opacity: 0.79
            }


            CustomButton {
                id: closeButton
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 5
                iconName: "images/toolbar/search-clear"
                visible: true
                onClicked: {
                    console.log("clicked !")
                    Cangote.models.searchModel.closeSearch(rowIndex)
                }
            }

            states: [
                State {
                    name: "normal"
                    when: !itemSelected
                    PropertyChanges { target: playlistText; color: "#ffffff" }
                    PropertyChanges { target: playlistText; styleColor: "#111111" }
                    PropertyChanges { target: playlistText; font.bold: false }
                },
                State {
                    name: "selectedActiveFocus"
                    when: itemSelected && tableView.activeFocus
                    PropertyChanges { target: playlistText; color: "#111111" }
                    PropertyChanges { target: playlistText; styleColor: "#dddddd" }
                    PropertyChanges { target: playlistText; font.bold: true }
                },
                State {
                    name: "selectedNoFocus"
                    when: itemSelected && !tableView.activeFocus
                    PropertyChanges { target: playlistText; color: "#ffffff" }
                    PropertyChanges { target: playlistText; styleColor: "#222222" }
                    PropertyChanges { target: playlistText; font.bold: true }
                }
            ]

        }
    }
}
