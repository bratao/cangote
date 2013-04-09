import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    anchors.fill: parent
    anchors.leftMargin: 10



    Column{
        anchors.fill:parent
        spacing: 10
        Label{
            text:"Connection"
            font.pixelSize: 30
        }

        Row
        {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 10
            GroupBox
            {
                title: "Tcp"
                checkable: true
                Column
                {
                    Row{
                        Label{
                            text:"Port:"
                            width: 100
                        }
                        SpinBox{
                            id: tcpPortSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                        }
                    }
                    Row{
                        Label{
                            text:"Advertised Port:"
                            width: 100
                        }
                        SpinBox{
                            id: tcpAdvertisedPortSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                        }
                    }
                    Row{
                        Label{
                            text:"Max connections:"
                            width: 100
                        }
                        SpinBox{
                            id: tcpMaxConnectionsSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                        }
                    }
                }
            }
            GroupBox
            {
                title: "Udp"
                checkable: true
                Column
                {
                    Row{
                        Label{
                            text:"Port:"
                            width: 100
                        }
                        SpinBox{
                            id: udpPortSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                        }
                    }
                    Row{
                        Label{
                            text:"Advertised Port:"
                            width: 100
                        }
                        SpinBox{
                            id: udpAdvertisedPortSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                        }
                    }
                    Row{
                        Label{
                            text:"Max BPS:"
                            width: 100
                        }
                        SpinBox{
                            id: udpMaxBPSSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 1000000
                        }
                    }
                }
            }

        }

        Row
        {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 10
            GroupBox
            {
                title: "Connectivity"
                Column
                {
                    CheckBox
                    {
                        text: "Use IPV6"
                    }
                    Row{
                        Label{
                            text:"Download(Kbps):"
                            width: 100
                        }
                        SpinBox{
                            id: downloadSpeedSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 100000
                        }
                    }
                    Row{
                        Label{
                            text:"Upload (Kbps):"
                            width: 100
                        }
                        SpinBox{
                            id: uploadSpeedSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 100000
                        }
                    }
                    Row{
                        Label{
                            text:"Max connected neighbours:"
                            width: 100
                        }
                        SpinBox{
                            id: maxNeighboursSpinBox
                            width: 80
                            minimumValue: 1
                            maximumValue: 10000
                        }
                    }
                }
            }
            GroupBox
            {
                title: "NAT"
                Column
                {
                    CheckBox
                    {
                        text: "I'm behind a NAT"
                    }
                    CheckBox
                    {
                        text: "NAT ports have been opened manually"
                    }
                    CheckBox
                    {
                        text: "Use UPnP"
                    }
                    CheckBox
                    {
                        text: "Use ICMP method"
                    }
                    Row{
                        Label{
                            text:"External (public) IPV4 address:"
                            width: 200
                        }
                        TextField{
                            id: ipv4Addr
                            width: 80
                        }
                    }
                }
            }

        }


    }
}
