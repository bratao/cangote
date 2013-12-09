import QtQuick 2.2
import QtQuick.Controls 1.1


//The tooltip
Rectangle {
    property string searchTerm
    property var metadata: null

    width: 300; height: 200
    visible: false
    color: "beige"
    opacity: 0.7
    z:100
    /*Text {
        anchors.centerIn: parent
        text: searchTerm
    }*/



    ListView {
        id: tableMeta
        model:metadata
        anchors.fill: parent

        delegate: Text {
            text: name + ": " + value
        }
    }


}
