import QtQuick 2.0
import QtQuick.Controls 1.0
import "Network"
import "Search"
import "Transfer"
import "Shared"
import "Sidebar"
SplitView {
    id: centerRoot
    property alias source: mainView.currentIndex
    property alias search: searchTab.item

    SideBar
    {
        width: 200
    }

    TabView {
        id:mainView

        frameVisible: false
        tabsVisible: false

/*
        Tab {
           active: true
           Browser{
           }
        }*/

        Tab {
           active: true
           Network{
           }
        }

        Tab {
           id: searchTab
           active: true

           Search{
               id: searchScreen
           }
        }

        Tab {
            active: true
            Transfers{
            }
        }
        Tab {
           active: true
           Shared{
           }
        }

    }
}
