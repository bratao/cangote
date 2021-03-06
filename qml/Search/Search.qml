import QtQuick 2.1
import QtQuick.Controls 1.0
import Cangote 1.0

Item{
    property alias visibleIndex: tabsView.currentIndex

    anchors.fill: parent
    id: searchTabs


    TabView {
        anchors.fill: parent
        frameVisible: false
        tabsVisible: false
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
            //tab.title = item.myTerm
            tab.active = 1
            tab.item.searchResultModel = Cangote.models.searchModel.getSearch(index).model

        }
        onItemRemoved: {
            var component = tabsView.getTab(index).item
            component.searchResultModel = null
            //component.destroy()
            tabsView.removeTab(index)



        }
    }



}
