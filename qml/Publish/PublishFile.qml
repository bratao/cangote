import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import Cangote 1.0
Window {
    id: publishWnd
    modality :Qt.ApplicationModal
    width: 600
    height: 400

    title: "Publish Files"


    Item{
        anchors.fill: parent
        Column{
            id: leftColumn
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: rightColumn.left
            TableView{
                width: parent.width
                model: Cangote.models.publishModel
                TableViewColumn{ role: "name"  ; title: "Name" ; width: 200 }
            }

            GroupBox{
                id: buttonsGroup
                width: parent.width
                height:30
                flat: true
                RowLayout{

                    Button{
                        text: "Add File"

                        onClicked: {
                            var file = Utils.openFilePicker();
                            Cangote.gnunet.publish.addFiles(file);
                        }
                    }
                    Button{
                        text: "Add Folder"
                    }
                }
            }


            GroupBox{
                title : "Namespace"
                width: parent.width
                height: 150
                Column {
                    ExclusiveGroup { id: group }
                    RadioButton {
                        text: qsTr("Global Namespace")
                        exclusiveGroup: group
                        checked: true
                    }
                    RadioButton {
                        text: qsTr("My own namespace")
                        exclusiveGroup: group
                    }
                }
            }
        }
        Column{
            id: rightColumn
            width: 300
            anchors.right: parent.right
            TabView{
                anchors.fill: parent
                Tab{
                    title:"Keywords"
                }
                Tab{
                    title:"Sharing"
                }
            }

        }

    }
}
