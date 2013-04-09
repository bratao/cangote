import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

import Cangote 1.0

ToolBar {
    id:toolbar

    BorderImage {

        border.bottom: 1
        anchors.fill: parent
        source: "images/toolbar/header-bg.png"
    }
    Row {
        id:toolbarButtons
        ToolButton {
            height: 50
            width: 50
            text: "Browser"
            onClicked:
            {
                center.source = 0;

            }
        }
        ToolButton {
            height: 50
            width: 50
            text: "Network"
            onClicked:
            {
                center.source = 1;
            }
        }
        ToolButton {
            height: 50
            width: 50
            text: "Search"
            onClicked:
            {
                center.source = 2;
            }
        }
        ToolButton {
            height: 50
            width: 50
            text: "Transfer"
            onClicked:
            {
                center.source = 3;
            }

        }

        ToolButton {
            height: 50
            width: 50
            text: "Shared"
            onClicked:
            {
                center.source = 4;
            }

        }

        ToolButton {
            height: 50
            width: 70
            text: "Preferences"
            onClicked:
            {
                window1.visible = !window1.visible
            }

        }
    }

    TextField {
        id: searchField
        //anchors.bottom: toolbarButtons.bottom
        anchors.verticalCenter : toolbar.verticalCenter
        //anchors.left: toolbarButtons.right
        //anchors.leftMargin: 8
        anchors.right: toolbar.right
        placeholderText: "Search"
        font.family: "Arial"
        font.pixelSize: 12
        width: 225
        Keys.onReturnPressed: doSearch()
        Keys.onEnterPressed: doSearch()

        function doSearch() {
            if (text.length) {
                Cangote.gnunet.filesharing.search(text,0);
            }
        }

        style: TextFieldStyle {
            leftMargin: 30
            rightMargin: 25

            background: BorderImage {
                border.left: 14
                border.right: 14
                border.top: 14
                border.bottom: 14
                source: searchField.activeFocus ? "images/toolbar/search-bg-focus.png" : "images/toolbar/search-bg.png"
            }
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 8
            source: "images/toolbar/search_glass.png"
        }

        CustomButton {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            iconName: "images/toolbar/search-clear"
            anchors.rightMargin: 6
            visible: searchField.text.length
            onClicked: searchField.text = ""
        }
    }
}


