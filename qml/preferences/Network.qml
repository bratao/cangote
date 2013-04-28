import QtQuick 2.1
import QtQuick.Controls 1.0
import Cangote 1.0

Item {
    anchors.fill: parent
    anchors.leftMargin: 10

    Column {
        spacing: 9

        Label
        {
            text: "Network"
            font.pixelSize: 30
        }


        CheckBox {
            id: transmitingUnsolicitedContent
            text: "Enable transmiting unsolicited content transmission from this peer"
            width: 100
            checked: Preferences.pushingContent
            onCheckedChanged: {
                Preferences.pushingContent = checked
            }
        }
        CheckBox {
            id: frameCheckbox
            text: "Enable caching content from the network at this peer"
            width: 100
            checked: Preferences.cachingContent
            onCheckedChanged: {
                Preferences.cachingContent = checked
            }
        }


        Row
        {
            spacing: 10
            Label {
                id: labelDataStore
                text: "Datastore Quota (Mbytes)"
                width: 150
            }
            Slider {
                id: sliderDataStore
                width: 300

                tickmarksEnabled: true
                minimumValue: 100
                maximumValue: 100000
                stepSize: 100
                value: Preferences.datastoreSize

                onValueChanged: {
                    //Preferences.datastoreSize = value
                    if(spinBoxDataStore != null)
                        spinBoxDataStore.value = value;
                }
            }
            SpinBox {
                id: spinBoxDataStore
                minimumValue: 100
                maximumValue: 100000
                width:80
                value: Preferences.datastoreSize
                onValueChanged: {
                    if(spinBoxDataStore != null)
                        sliderDataStore.value = value;
                    Preferences.datastoreSize = value
                }
            }

        }


        Row
        {
            spacing: 10
            Label {
                id: label1
                text: "Datacache Quota (Mbytes)"
                width: 150
            }
            Slider {
                id: sliderDataCache
                width: 300

                tickmarksEnabled: true

                minimumValue: 100
                maximumValue: 100000
                stepSize: 100
                value: Preferences.datacacheSize
                onValueChanged: {
                    //Preferences.datacacheSize = value
                    if(spinBoxDataCache!= null)
                       spinBoxDataCache.value = value;
                }
            }
            SpinBox {
                id: spinBoxDataCache
                minimumValue: 100
                maximumValue: 100000
                width:80
                value: Preferences.datacacheSize
                onValueChanged: {
                    Preferences.datacacheSize = value
                    //if(spinBoxDataCache!= null)
                    //    spinBoxDataCache.value = value;
                }
            }

        }

        GroupBox
        {
            checkable: true
            title: "Friend-to-Friend configuration"
            Column
            {
                spacing: 10
                CheckBox
                {
                    text: "Friend to Friend only"
                    checked: Preferences.friendToFriendOnly
                    onCheckedChanged: {
                        Preferences.friendToFriendOnly = checked
                    }
                }
                Row{
                    spacing: 5
                    Label{
                        text: "Connect to at least:"
                    }
                    SpinBox
                    {
                        id: numberFriendsSpinbox
                        width: 50
                        value: Preferences.minimalNumberOfFriends
                        onValueChanged: {
                            Preferences.minimalNumberOfFriends = value
                        }
                    }
                    Label{
                        text: "Friends"
                    }
                }

            }
        }

        GroupBox
        {
            checkable: true
            title: "Host List"
            Row
            {
                Column
                {
                    spacing: 10
                    CheckBox
                    {
                        text: "Use Hostlists to bootstrap"
                        checked: Preferences.hostlistsEnabled
                        onCheckedChanged: {
                            Preferences.hostlistsEnabled = checked
                        }
                    }
                    CheckBox
                    {
                        text: "Learn servers from p2p"
                        checked: Preferences.learnHostslistsFromNetworkEnabled
                        onCheckedChanged: {
                            Preferences.learnHostslistsFromNetworkEnabled = checked
                        }
                    }
                }
                Column
                {
                    TextField{
                        text:Preferences.hostlist
                        onTextChanged: {
                            Preferences.hostlist = text
                        }
                    }
                }
            }
        }
    }
}
