import QtQuick 2.0
import QtQuick.Controls 1.0

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
            checked: true
            width: 100
        }
        CheckBox {
            id: frameCheckbox
            text: "Enable caching content from the network at this peer"
            checked: true
            width: 100
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

                value : 1000
                minimumValue: 100
                maximumValue: 10000
                stepSize: 10

                onValueChanged: {
                    if(spinBoxDataStore != null)
                        spinBoxDataStore.value = value;
                }
            }
            SpinBox {
                id: spinBoxDataStore
                minimumValue: 100
                maximumValue: 10000
                value: sliderDataStore.value
                width:80
                onValueChanged: {
                    if(spinBoxDataStore != null)
                        sliderDataStore.value = value;
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

                value : 1000
                minimumValue: 100
                maximumValue: 10000
                stepSize: 10
                onValueChanged: {
                    if(spinBoxDataCache!= null)
                        spinBoxDataCache.value = value;
                }
            }
            SpinBox {
                id: spinBoxDataCache
                minimumValue: 100
                maximumValue: 10000
                value: sliderDataCache.value
                width:80
                onValueChanged: {
                    if(sliderDataCache!= null)
                        sliderDataCache.value = value;
                }
            }

        }

        GroupBox
        {
            title: "Friend-to-Friend configuration"
            Column
            {
                spacing: 10
                CheckBox
                {
                    text: "Friend to Friend only"
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
                    }
                    Label{
                        text: "Friends"
                    }
                }

            }
        }

        GroupBox
        {
            title: "Host List"
            Row
            {
                Column
                {
                    spacing: 10
                    CheckBox
                    {
                        text: "Use Hostlists to bootstrap"
                    }
                    CheckBox
                    {
                        text: "Learn servers from p2p"
                    }
                }
                Column
                {
                    /*TextArea
                    {

                    }*/
                }
            }
        }
    }
}
