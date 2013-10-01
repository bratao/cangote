import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.0
import Cangote 1.0

StatusBar {
    height: 20
    //color : "lightgrey"

    property bool needTooltip: statusIcon.hovered
      property real tooltipX: statusIcon.mouseX
      property real tooltipY: statusIcon.mouseY


    Rectangle {
        id: tooltip
        width: 75; height: 20
        visible: false
        color: "red"
        z:100
        Text {
            anchors.centerIn: parent
            text: "My Tooltip"
        }

        states: State {
            name: "inuse"
            when: needTooltip
            PropertyChanges {
                target: tooltip
                visible: true
                x: tooltipX
                y: tooltipY
            }
        }
    }


    RowLayout{
        anchors.verticalCenter: parent.verticalCenter
        Rectangle{
            id:statusIcon
            property bool hovered: ma.containsMouse
            property int mouseX: ma.mouseX
            property int mouseY: ma.mouseY
            height: 15
            width: 15
            radius: 20
            color: Cangote.connected ? "green": "red"

            MouseArea{
                id: ma
                anchors.fill: parent
                hoverEnabled: true

                onHoveredChanged: {

                }
            }
        }

        Text{
            text: qsTr("Connected to: ") + Cangote.status.connectedPeers + qsTr(" peers") +
                  "(" + Cangote.status.estimatedNodes + ")"
            renderType: Text.NativeRendering
        }

        Text{
            text: qsTr("In: ") + Cangote.status.incomingBand + qsTr(" K/b ") +
                  qsTr("Out: ") + Cangote.status.outgoingBand + qsTr(" K/b ")
            renderType: Text.NativeRendering
        }
    }

}
