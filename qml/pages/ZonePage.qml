import QtQuick 2.0
import Sailfish.Silica 1.0
import subtrains 1.0


Page {
    id: zoneDialog
    signal accepted(int id, string text)
    property QmlHandler qmlHandler

    // Заголовок
    PageHeader {
        title: qsTr("Регионы")
        id: zonePageHeader
        height: Theme.itemSizeLarge
    }

    property var timeZoneId: {return null}
    SilicaListView {
        id: listView
        model: ListModel {}
        anchors.fill: parent
        anchors.topMargin: Theme.itemSizeLarge

        function getZonesLike(text) {
             return qmlHandler.getZonesLike(text);
        }

        function getAllZones() {
             return qmlHandler.getAllZones();
        }

        delegate: BackgroundItem {
            id: delegate

            Label {
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter

                elide: Text.ElideRight

                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
                text: title //name
            }
            onClicked: {
                zoneDialog.accepted(code, title);
                pageStack.pop();
            }
        }
        Component.onCompleted: {
            var results = getAllZones();
            for (var i in results) {
                listView.model.append(results[i]);
            }
        }
        VerticalScrollDecorator {}
    }
}






