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

    Window{
        id: progressWnd
        modality :Qt.ApplicationModal
        width: 300
        height: 100
        visible: Cangote.status.isPublishing

        title: "Progress"

        RowLayout{
            anchors.fill: parent

            ProgressBar{
                minimumValue: 0
                maximumValue: 100
                value: Cangote.status.publishingPercentage
            }
        }

    }


    ColumnLayout{
        anchors.fill: parent
        RowLayout{
            id: leftLayout
            anchors.fill: parent
            ColumnLayout{
                id: leftColumn
                Layout.fillWidth: true
                Layout.fillHeight: true
                TableView{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumHeight: 50
                    model: Cangote.models.publishModel
                    TableViewColumn{ role: "name"  ; title: "Name"}

                    onCurrentRowChanged:
                    {
                        var file = Cangote.models.publishModel.getPublishedFile(currentRow)
                        file.set
                        publishDetails.keywordModel = file ? file.keywordModel : null
                        publishDetails.metadataModel = file ? file.metadataModel : null
                        console.log(file)
                        if(file && file.haveThumbnail)
                        {
                            console.log(file)
                            publishDetails.thumbnailImage = "image://publishThumbnail/"+ currentRow
                        }
                        else
                        {
                            console.log("I dont have a file")
                            publishDetails.thumbnailImage = null // TODO: No thumbnail image
                        }
                    }

                }

                GroupBox{
                    id: buttonsGroup
                    flat: true
                    Layout.fillWidth: true
                    RowLayout{

                        Button{
                            text: "Add File"

                            onClicked: {
                                Cangote.gnunet.publish.filePicker();
                            }
                        }
                        Button{
                            text: "Add Folder"

                            onClicked: {
                                progressWnd.visible = true
                            }
                        }
                    }
                }

                TabView{
                    Layout.fillWidth: true
                    Layout.minimumHeight: 80
                    Tab{
                        title:"Publication"
                    }
                    Tab{
                        title:"Namespace"

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

            }
            PublishDetails{
                id: publishDetails
                Layout.fillWidth: true
                Layout.fillHeight:  true
                Layout.minimumWidth:200
            }


        }
        Rectangle{
            Layout.fillWidth: true
            Layout.minimumHeight: 25
            RowLayout{
                anchors.right: parent.right
                anchors.bottomMargin: 5
                Button{
                    text: qsTr("Publish")

                    onClicked: {
                        Cangote.gnunet.publish.publishItems();
                        publishWnd.close()
                    }

                }
                Button{
                    text: qsTr("Cancel")

                    onClicked: {
                        publishWnd.close()
                    }
                }
            }
        }


    }
}
