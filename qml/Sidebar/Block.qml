import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0


Rectangle {
    property var model: null
    property bool selected: false
    property alias itemSelected:list.currentIndex

    signal headerClicked
    signal changed(int indexChanged)

    id:block
    property string title
    color: "#474747"
    width: parent.width
    height: 18 + (list.count*20)




    BorderImage {
        id: titleBackground
        width: parent.width
        height: 18
        Text {
            id: titleLabel
            font.pixelSize: 15
            color: "grey"
            text: title
            width: block.width
            elide: Text.ElideRight

            states: [
                State {
                    name: "normal"
                    when: !mousearea.containsMouse && !selected
                    PropertyChanges { target: titleLabel; color: "#ffffff" }

                },
                State {
                    name: "selected"
                    when: selected
                    PropertyChanges { target: titleLabel; color: "#000" }
                    PropertyChanges { target: titleBackground; source: "images/itemlistselectedfocus.png" }
                },
                State {
                    name: "over"
                    when: mousearea.containsMouse
                    PropertyChanges { target: titleLabel; color: "#bea" }
                }
            ]


            MouseArea{
                id: mousearea
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    block.headerClicked()
                }

            }
        }
    }



    ListView{
        id: list
        model: parent.model
        focus: true
        anchors.top: titleBackground.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        boundsBehavior :
            Flickable.StopAtBounds

        delegate: BlockDelegate{}

        onCurrentIndexChanged: {
            block.changed(currentIndex)
        }

    }

}

