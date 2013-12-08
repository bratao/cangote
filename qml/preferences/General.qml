import QtQuick 2.2
import QtQuick.Controls 1.1
import Cangote 1.0

Item {
    anchors.fill: parent
    anchors.leftMargin: 10



    Column{
        Label{
            text:"General"
            font.pixelSize: 30
        }

        CheckBox{
            text: "Check for new versions"
            checked: Preferences.checkNewVersion
            onCheckedChanged: {
                Preferences.checkNewVersion = checked
            }
        }

        CheckBox{
            text: "Minimize to System Tray"
            checked: Preferences.minimizeToTray
            onCheckedChanged: {
                Preferences.minimizeToTray = checked
            }
        }


    }
}
