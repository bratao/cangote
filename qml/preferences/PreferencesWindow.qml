import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0

import Cangote 1.0

Window {
    id: preferencesWnd

    width: 800
    height: 600

    title: "Preferences"

    onVisibleChanged: {
        Preferences.save();
    }

    ListModel {
        id: libraryModel
        ListElement{ name: "General";         tabId: 0  }
        ListElement{ name: "Directories";     tabId: 1  }
        ListElement{ name: "Connection";      tabId: 2  }
        ListElement{ name: "Network";         tabId: 3  }
        ListElement{ name: "Advanced";        tabId: 4  }
    }


    Row {
        anchors.fill:parent
        Rectangle {
            width: 220; height: parent.height
            color: "#efefef"

            ListView {
                focus: true
                id: categories
                anchors.fill: parent
                model: libraryModel
                delegate: CategoryDelegate {}
                highlight: Rectangle { color: "steelblue" }
                highlightMoveVelocity: 1000
            }
            ScrollBar {
                scrollArea: categories; height: categories.height; width: 8
                anchors.right: categories.right
            }
        }
        TabView {
            id: tab
            width: parent.width - 220; height: parent.height
            tabsVisible: false
            //frame: false

            Tab {
                General
                {

                }
            }

            Tab {
                Directories
                {

                }
            }

            Tab {
                Connection
                {

                }
            }

            Tab {
                Network
                {

                }
            }
            Tab {
                Advanced
                {

                }
            }

        }
    }
}

