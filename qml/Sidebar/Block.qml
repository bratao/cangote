import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0


Rectangle {
    id:block
    property string title
    color: "#474747"


    Text {
        id: titleLabel
        font.pixelSize: 15
        color: "grey"
        text: title
        width: block.width
        elide: Text.ElideRight
    }



    ListView{
        model: Cangote.models.searchModel
        focus: true
        anchors.top: titleLabel.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        boundsBehavior :
            Flickable.StopAtBounds

        delegate: BlockDelegate{}

    }

}

