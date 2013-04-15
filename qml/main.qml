
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
            title: "File"
            MenuItem { text: "Quit"; onTriggered: Qt.quit() }
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
