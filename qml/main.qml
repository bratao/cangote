
import QtQuick 2.2
import QtQuick.Controls 1.1
import Cangote 1.0
import "preferences"


ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300

    onClosing: {

        if(Preferences.minimizeToTray){
            close.accepted = false;
            Cangote.onClose();
        }
    }



    menuBar: MenuBar {
        Menu {
            title: qsTr("Network")
            MenuItem {
                text: qsTr("My Info");
                onTriggered: {
                    var myInfo = Qt.createComponent("Network/MyInfo.qml");
                    var myInfoWnd = myInfo.createObject();

                    myInfoWnd.show();
                }
            }
            MenuItem {
                text: qsTr("Add new peer");
                onTriggered: {
                    var addPeer = Qt.createComponent("Network/AddPeer.qml");
                    var addPeerWnd = addPeer.createObject();

                    addPeerWnd.show();
                }
            }
        }
        Menu {
            title: qsTr("Tools")
            MenuItem {
                text: qsTr("Preferences");
                onTriggered: {
                    var preferences = Qt.createComponent("preferences/PreferencesWindow.qml");
                    var preferencesWnd = preferences.createObject();

                    preferencesWnd.show();
                }
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem { text: "About..."; enabled: false }
        }
    }

    toolBar: Header {
        id: header
        //anchors.top: parent.top
       // width: parent.width

       // onSearchRequested: center.showSearchResults(header.search)
    }

    Center {
        id: center
        anchors.fill: parent
    }

    statusBar: Footer {
        id: footer
        //anchors.bottom: parent.bottom
        //width: parent.width
    }


}
