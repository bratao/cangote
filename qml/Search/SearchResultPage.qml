import QtQuick 2.0
import QtQuick.Controls 1.0


Item {
    property string searchTerm
    property var searchModel

     anchors.fill: parent

     TableView
     {
         anchors.fill: parent
         model: searchModel

         TableViewColumn
         {
             title: "Name"
             role: "filename"
         }

         TableViewColumn
         {
             title: "Size"
             role: "filesize"
         }

     }

}
