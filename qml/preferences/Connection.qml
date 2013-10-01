import QtQuick 2.1
import QtQuick.Controls 1.0
import Cangote 1.0

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
                title: "Use TCP transport"
                checkable: true
                checked: Preferences.tcpEnabled
                onCheckedChanged: {
                    Preferences.tcpEnabled = checked
                }
                Column
                {
                    Row{
                        Label{
                            text:"Port:"
                            width: 100
                        }
                        SpinBox{
                            id: tcpPortSpinBox
                            value: Preferences.tcpPort
                            width: 80
                            minimumValue: 1
                            maximumValue: 65536
                            onValueChanged: {
                                Preferences.tcpPort = value
                            }
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
                            value: Preferences.tcpAdvertisedPort
                            onValueChanged: {
                                Preferences.tcpAdvertisedPort = value
                            }
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
                            value: Preferences.tcpMaxConnections
                            onValueChanged: {
                                Preferences.tcpMaxConnections = value
                            }
                        }
                    }
                }
            }
            GroupBox
            {
                title: "Use UDP transport"
                checkable: true
                checked: Preferences.udpEnabled
                onCheckedChanged: {
                    Preferences.udpEnabled = checked
                }
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
                            value: Preferences.udpPort
                            onValueChanged: {
                                Preferences.udpPort = value
                            }
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
                            value: Preferences.udpAdvertisedPort
                            onValueChanged: {
                                Preferences.udpAdvertisedPort = value
                            }
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
                            value: Preferences.udpMaxSpeed
                            onValueChanged: {
                                Preferences.udpMaxSpeed = value
                            }
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
                        checked: Preferences.ipv6Enabled
                        onCheckedChanged: {
                            Preferences.ipv6Enabled = checked
                        }

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
                            value: Preferences.downloadSpeed
                            onValueChanged: {
                                Preferences.downloadSpeed = value
                            }
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
                            value: Preferences.uploadSpeed
                            onValueChanged: {
                                Preferences.uploadSpeed = value
                            }
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
                            value: Preferences.neighboursLimit
                            onValueChanged: {
                                Preferences.neighboursLimit = value
                            }
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
                        checked: Preferences.behindNat
                        onCheckedChanged: {
                            Preferences.behindNat = checked
                        }
                    }
                    CheckBox
                    {
                        text: "NAT ports have been opened manually"
                        checked: Preferences.portsOpen
                        onCheckedChanged: {
                            Preferences.portsOpen = checked
                        }
                    }
                    CheckBox
                    {
                        text: "Use UPnP"
                        checked: Preferences.UPNPEnabled
                        onCheckedChanged: {
                            Preferences.UPNPEnabled = checked
                        }
                    }
                    CheckBox
                    {
                        text: "Use ICMP method"
                        checked: Preferences.ICMPMethod
                        onCheckedChanged: {
                            Preferences.ICMPMethod = checked
                        }
                    }
                    Row{
                        Label{
                            text:"External (public) IPV4 address:"
                            width: 200
                        }
                        TextField{
                            id: ipv4Addr
                            width: 80
                            text: Preferences.externalIpv4Address
                            onTextChanged: {
                                Preferences.externalIpv4Address = text
                            }
                        }
                    }
                }
            }

        }


    }
}
