import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1
import Cangote 1.0

Column {
    anchors.fill: parent
    spacing: 5
    anchors.leftMargin: 10

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


    RowLayout
    {
        spacing: 10
        Label {
            id: labelDataStore
            text: "Datastore (persistent storage) Quota (GB)"
            width: 150
        }

        Slider {
            id: sliderDataStore
            width: 300
            tickmarksEnabled: true
            minimumValue: 0.1
            maximumValue: 30
            stepSize: 0.1
            value: Preferences.datastoreSize


            onValueChanged: {
                //Preferences.datastoreSize = value
                if(spinBoxDataStore != null)
                    spinBoxDataStore.value = value;
            }
        }
        SpinBox {
            id: spinBoxDataStore
            minimumValue: 0.1
            maximumValue: 30
            decimals: 2
            width:80
            stepSize : 0.1
            value: Preferences.datastoreSize
            onValueChanged: {
                if(spinBoxDataStore != null)
                    sliderDataStore.value = value;
                Preferences.datastoreSize = value
            }
        }

    }


    RowLayout
    {
        spacing: 10
        Label {
            id: label1
            text: "Datacache (temporary storage) Quota (Mbytes)"
            width: 150
        }
        Slider {
            id: sliderDataCache
            width: 300

            tickmarksEnabled: true

            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: Preferences.datacacheSize
            onValueChanged: {
                //Preferences.datacacheSize = value
                if(spinBoxDataCache!= null)
                    spinBoxDataCache.value = value;
            }
        }
        SpinBox {
            id: spinBoxDataCache
            minimumValue: 1
            maximumValue: 100
            width:80
            value: Preferences.datacacheSize
            onValueChanged: {
                Preferences.datacacheSize = value
                //if(spinBoxDataCache!= null)
                //    spinBoxDataCache.value = value;
            }
        }

    }

    RowLayout{
        GroupBox
        {
            checkable: false
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
            checkable: false
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
