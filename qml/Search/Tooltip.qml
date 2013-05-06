import QtQuick 2.0


//The tooltip
Rectangle {
    property string searchTerm

    width: 300; height: 200
    visible: false
    color: "beige"
    opacity: 0.7
    z:100
    Text {
        anchors.centerIn: parent
        text: searchTerm
    }
}
