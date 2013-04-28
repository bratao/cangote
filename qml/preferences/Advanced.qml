import QtQuick 2.1
import QtQml.Models 2.1
import QtQuick.Controls 1.0

Rectangle {
    ObjectModel {
        id: itemModel
        Row{ Label{ text:"Advertised Port:"; font.pointSize: 10; width: 400;} SpinBox{ }  }
        Row{ Label{ text:"Advertised Port:"; font.pointSize: 10; width: 400;} SpinBox{ }  }
        Row{ Label{ text:"Advertised Port:"; font.pointSize: 10; width: 400;} SpinBox{ }  }
    }


    ListView {
        id:list
        anchors.fill: parent
        model: itemModel
        focus: true
    }
}
