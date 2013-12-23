import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

//The tooltip
Rectangle {
    property string searchTerm
    property var metadata: null

    width: 300; height: 200
    visible: false
    color: "#F7F7F7"
    opacity: 1.0
    z:100
    /*Text {
        anchors.centerIn: parent
        text: searchTerm
    }*/



    ListView {
        id: tableMeta
        model:metadata
        anchors.fill: parent

        delegate: Item {
            //anchors.fill: parent
            height: 15
            width: parent.width
            RowLayout{
                anchors.fill: parent
                //color: "lightgrey"
                Rectangle{
                    width: 120
                    height: 15
                    color: "#F7F7F7"
                    Text {
                        width: 120
                        id: nameText
                        text: name + " :"
                        renderType : Text.NativeRendering
                        elide: Text.ElideRight
                    }
                }


                //color: "lightgrey"
                Text {
                    Layout.fillWidth: true
                    height: 15
                    id: valueText
                    text: value
                    elide: Text.ElideRight
                }



            }

        }
    }


}
