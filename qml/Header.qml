import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0


ToolBar {
    id:toolbar
    height: 40

    style: ToolBarStyle{
        padding.left: 0
        padding.right: 0
        padding.top: 0
        padding.bottom: 0
    }

    BorderImage {


        border.bottom: 1
        anchors.fill: parent
        source: "images/toolbar/header-bg.png"
    }
    Row {
        id:toolbarButtons
        height: 40
        TextField {
            id: searchField
            //anchors.bottom: toolbarButtons.bottom
            anchors.verticalCenter : parent.verticalCenter
            //anchors.left: toolbarButtons.right
            //anchors.leftMargin: 8
            //anchors.right: toolbar.right
            placeholderText: "Search"
            font.family: "Arial"
            font.pixelSize: 12
            width: 225
            //height: 30
            Keys.onReturnPressed: doSearch()
            Keys.onEnterPressed: doSearch()


            function doSearch() {
                if (text.length) {
                    Cangote.gnunet.filesharing.search(text,0);
                }
            }

            style: TextFieldStyle {
                padding { top: 4 ; left: 30 ; right: 25 ; bottom:4 }

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
                height: 15
                width: 15
                visible: searchField.text.length
                onClicked: searchField.text = ""
            }
        }

        Rectangle{
            color: "grey"
            anchors.verticalCenter: parent.verticalCenter
            width: 1
            height: parent.height -5
        }

        ToolButton {
            height: 40
            width: 70
            text: "Preferences"
            onClicked:
            {
                var preferences = Qt.createComponent("preferences/PreferencesWindow.qml");
                var preferencesObj = preferences.createObject();

                preferencesObj.visible =true

            }

        }

        ToolButton {
            height: 40
            width: 70
            text: "Publish files"
            onClicked:
            {
                var publish = Qt.createComponent("Publish/PublishFile.qml");
                var publishObj = publish.createObject();

                publishObj.visible =true

            }

        }

    }


}


