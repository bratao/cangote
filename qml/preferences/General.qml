import QtQuick 2.1
import QtQuick.Controls 1.0

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

    }
}
