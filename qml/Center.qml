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

    SideBar
    {
        width: 200
    }

    TabView {
        id:mainView

        frameVisible: false
        tabsVisible: false


        Tab {
           active: true
           Browser{
           }
        }

        Tab {
           active: true
           Network{
           }
        }

        Tab {
           active: true
           Search{
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
