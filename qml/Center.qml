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
           Browser{
           }
        }

        Tab {
           Network{
           }
        }

        Tab {
           Search{
           }
        }
        Tab {
            Transfers{
            }
        }
        Tab {
           Shared{
           }
        }

    }
}
