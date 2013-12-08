import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0

Window {
    id: firstRunWnd

    width: 600
    height: 400

    title: "Welcome to Cangote"


    ColumnLayout{
        anchors.fill: parent

        Rectangle{
            id:header
            color: "lightgrey"
            height: 50
            Layout.fillWidth: true
            Label {
                id: titleLabel
                font.bold: true
                font.pointSize: 19
                text: qsTr("Welcome !")
                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
            }

        }




        TabView{
            id: tabView
            Layout.fillWidth: true
            Layout.fillHeight: true
            frameVisible: false
            tabsVisible:false

            Tab{
                Welcome{
                }

            }

            Tab{
                End{
                }
            }

        }
        RowLayout{
            Layout.alignment: Qt.AlignRight
            Button{
                text: "Previous"
                height: 30
                width: 100
                onClicked: {
                    tabView.currentIndex = tabView.currentIndex - 1
                }
            }
            Button{
                text: "Next"
                height: 30
                width: 100
                onClicked: {
                    tabView.currentIndex = tabView.currentIndex + 1
                }
            }
        }

    }

}
