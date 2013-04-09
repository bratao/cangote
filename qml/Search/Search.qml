import QtQuick 2.0
import QtQuick.Controls 1.0
import Cangote 1.0

Item{
    anchors.fill: parent

    id: searchTabs

    Component {
        id: mytab
        Label {
            text: "oie !"
        }
    }

        /*
        TableView
        {
           model : Cangote.models.searchModel

           TableViewColumn
           {
               role: "id"
               title: "ID"
               width: 120
           }
        }
*/

    TabView {
    anchors.fill: parent
    id: tabsView

    }


    Repeater
    {
        id: repeater
        model : Cangote.models.searchModel
        Item
        {
            property string myTerm: term

        }
        onItemAdded: {
            var component = Qt.createComponent("SearchResultPage.qml");
            var tab = tabsView.addTab(item.myTerm, component)
            tab.title = item.myTerm
            //console.log(tab)
           // console.log(tab.children[0])
            //tab.children[0] = item.myTerm
            //tab.children[0].searchModel = Cangote.models.searchModel.getSearch(index).model

        }
        onItemRemoved: {
            tabsView.removeTab(index)
        }
    }



}
