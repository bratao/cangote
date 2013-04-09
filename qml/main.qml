
import QtQuick 2.0
import QtQuick.Controls 1.0
import "preferences"

ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300


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


    PreferencesWindow { id: window1 }


}
