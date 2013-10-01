import QtQuick 2.1
import QtQuick.Controls 1.0
import Cangote 1.0

Item {
    anchors.fill: parent
    anchors.leftMargin: 10



    Column{
        spacing: 50
        Label{
            text:"Directories"
            font.pixelSize: 30
        }

        Row{
            width: parent.width
            GroupBox {
                title: qsTr("Location of Downloaded Files")
                width: 500
                height: 50
                Row{
                    TextField {
                        id: folderText
                        text: Preferences.downloadDirectory
                        width: 300
                        height: 25
                        font.pixelSize: 12
                    }
                    Button{
                        width: 25
                        height: 25
                        text: "..."

                        onClicked: {
                            var folder =  Utils.openFolderPicker()
                            Preferences.downloadDirectory = folder;
                        }
                    }
                }
            }
        }


    }


}
