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
            tab.item.searchModel = Cangote.models.searchModel.getSearch(index).model

        }
        onItemRemoved: {
            tabsView.removeTab(index)

        }
    }



}
