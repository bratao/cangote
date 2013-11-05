import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Private 1.0

import Cangote 1.0


ToolBar {



    property int searchType: 0



    Menu {
        id: contextMenu

        MenuItem {
            iconSource: "filetypes/FileTypeAny.png"

            action:
                Action {
                text: "Any"
                onTriggered: {
                    searchType = 0;
                }
            }
        }
        MenuSeparator { }
        MenuItem {
            iconSource: "filetypes/FileTypeAudio.png"
            action:
                Action {
                text: "Audio"
                onTriggered: {
                    searchType = 1;
                }
            }
        }
        MenuItem {
            iconSource: "filetypes/FileTypeVideo.png"
            action:
                Action {
                text: "Video"
                onTriggered: {
                    searchType = 2;
                }
            }
        }
        MenuItem {
            iconSource: "filetypes/FileTypePicture.png"
            action:
                Action {
                text: "Picture"
                onTriggered: {
                    searchType = 3;
                }
            }
        }
        MenuItem {
            iconSource: "filetypes/FileTypeProgram.png"
            action:
                Action {
                text: "Program"
                onTriggered: {
                    searchType = 4;
                }
            }
        }

        MenuItem {
            iconSource: "filetypes/FileTypeDocument.png"
            action:
                Action {
                text: "Documents"
                onTriggered: {
                     searchType = 5;
                }
            }
        }
        MenuItem {
            iconSource: "filetypes/FileTypeArchive.png"
            action:
                Action {
                text: "Archive"
                onTriggered: {
                    searchType = 6;
                }
            }
        }
        MenuItem {
            iconSource: "filetypes/FileTypeCDImage.png"
            action:
                Action {
                text: "CD-Image"
                onTriggered: {
                    searchType = 7;
                }
            }
        }



    }



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
                padding { top: 4 ; left: 35 ; right: 25 ; bottom:4 }

                background: BorderImage {
                    border.left: 14
                    border.right: 14
                    border.top: 14
                    border.bottom: 14
                    source: searchField.activeFocus ? "images/toolbar/search-bg-focus.png" : "images/toolbar/search-bg.png"
                }
            }


            Rectangle{
                id: iconRectangle
                color: "#F0F0F0"
                anchors.top: parent.top
                anchors.topMargin:  4
                anchors.left: parent.left
                anchors.leftMargin: 8
                height: 21
                width: 23
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left

                    source: {
                        if(searchType === 0)
                            return "filetypes/FileTypeAny.png"
                        else if(searchType === 1)
                            return "filetypes/FileTypeAudio.png"
                        else if(searchType === 2)
                            return "filetypes/FileTypeVideo.png"
                        else if(searchType === 3)
                            return "filetypes/FileTypePicture.png"
                        else if(searchType === 4)
                            return "filetypes/FileTypeProgram.png"
                        else if(searchType === 5)
                            return "filetypes/FileTypeDocument.png"
                        else if(searchType === 6)
                            return "filetypes/FileTypeArchive.png"
                        else if(searchType === 7)
                            return "filetypes/FileTypeCDImage.png"


                    }
                }

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 17
                    source: "images/toolbar/search_arrow.png"
                }
                MouseArea{
                    id:ma
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        contextMenu.popup()
                    }


                }
            }

            Rectangle{
                color: "#C8C8C8"
                anchors.top: parent.top
                anchors.topMargin:  3
                anchors.left: iconRectangle.right
                height: iconRectangle.height +1
                width: 1
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

        CustomButton {
            iconName: "images/toolbar/search-button"
            height: 34
            width: 40
            hoverEnabled: true
            onClicked: {
                if(searchField.text.length)
                    Cangote.gnunet.filesharing.search(searchField.text,0);
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


