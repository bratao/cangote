
import QtQuick 2.1
import QtQuick.Controls 1.0
import "preferences"


ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300


    menuBar: MenuBar {
        Menu {
            title: qsTr("Network")
            MenuItem {
                text: qsTr("Add new peer");
                onTriggered: {
                    var addPeer = Qt.createComponent("Network/AddPeer.qml");
                    var addPeerObj = addPeer.createObject();

                    addPeerObj.visible = true;
                }
            }
        }
        Menu {
            title: qsTr("Tools")
            MenuItem {
                text: qsTr("Preferences");
                onTriggered: {
                    var preferences = Qt.createComponent("preferences/PreferencesWindow.qml");
                    var preferencesObj = preferences.createObject();

                    preferencesObj.visible = true;
                }
            }
        }
        Menu {
            title: "Help"
            MenuItem { text: "About..."; enabled: false }
        }
    }

    Header {
        id: header
        anchors.top: parent.top
        width: parent.width

       // onSearchRequested: center.showSearchResults(header.search)
    }

    Center {
        id: center
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: footer.top
    }

    Footer {
        id: footer
        anchors.bottom: parent.bottom
        width: parent.width
    }


}
