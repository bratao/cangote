import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

import "../"

Item {
    id: delegate

    width: delegate.ListView.view.width; height: 20

    property var itemSelected: delegate.ListView.isCurrentItem
    property bool itemHover: false

    BorderImage {
        id: rowBackground
        anchors.fill: parent
        states: [
            State {
                name: "normal"
                when: !itemSelected
                PropertyChanges { target: rowBackground; source: "" }
                PropertyChanges { target: playlistText; color: "#ffffff" }
                PropertyChanges { target: playlistText; styleColor: "#111111" }
                PropertyChanges { target: playlistText; font.bold: false }
            },
            State {
                name: "selectedActiveFocus"
                when: itemSelected //&& tableView.activeFocus
                PropertyChanges { target: rowBackground; source: "images/itemlistselectedfocus.png" }
                PropertyChanges { target: playlistText; color: "#111111" }
                PropertyChanges { target: playlistText; styleColor: "#dddddd" }
                PropertyChanges { target: playlistText; font.bold: true }
            },
            State {
                name: "selectedNoFocus"
                when: itemSelected && !tableView.activeFocus
                PropertyChanges { target: rowBackground; source: "images/itemlistselected.png" }
                PropertyChanges { target: playlistText; color: "#ffffff" }
                PropertyChanges { target: playlistText; styleColor: "#222222" }
                PropertyChanges { target: playlistText; font.bold: true }
            }
        ]



        Image {
            id: playlistImage
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 15
            source: "images/playlist"+ (itemSelected /*&& delegate.ListView.activeFocus*/ ? "-activefocus" : "")
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
            text: term
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
            height: 15
            width: 15
            visible: true
            onClicked: {
                console.log("clicked !")
                Cangote.models.searchModel.closeSearch(index)
            }
        }

        MouseArea {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: closeButton.left

            preventStealing: true
            propagateComposedEvents: true
            onClicked: {
                delegate.ListView.view.currentIndex = index
                // tab.currentIndex = tabId
            }


        }

    }
}
