import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ColumnLayout{
    property var metadataModel
    property var keywordModel
    property var thumbnailImage
    Layout.fillWidth: true

    id: detailsColumn

    ColumnLayout{
        Layout.fillWidth: true
        height: 200
        Text{
            text: qsTr("Thumbnail")
            font.pixelSize: 15

        }
        Image {
            id: thumbnail
            width: 130; height: 100
            fillMode: Image.PreserveAspectFit
            smooth: true
            clip: true
            source: thumbnailImage
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    ColumnLayout{
        Layout.fillWidth: true
        Layout.fillHeight: true
        Text{
            text: qsTr("Metadata")
            font.pixelSize: 15

        }

        TableView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: metadataModel
            TableViewColumn{ role: "name"  ; title: "Name" ; width: 100 }
            TableViewColumn{ role: "value"  ; title: "Value" ; width: 100 }
        }
    }

    ColumnLayout{
        Layout.fillWidth: true
        Layout.fillHeight: true
        Text{
            text: qsTr("Keywords")
            font.pixelSize: 15

        }
        TableView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: keywordModel
            TableViewColumn{ role: "name"  ; title: "Value"}
        }

    }

}
