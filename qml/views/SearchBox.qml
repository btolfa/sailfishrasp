import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    property int currentZoneIndex: 1

    id: searchColumn
    property alias placeHolderText: searchField.placeholderText
    height: searchRow.height + hints.height
    width: parent.width

    property var stationEsr: null

    Row {
        id: searchRow
        spacing: Theme.paddingSmall
        width: parent.width

        SearchField {
            id: searchField
            placeholderText: "PlaceHolder text"
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - locateFrom.width - Theme.horizontalPageMargin - parent.spacing
            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: textArea.focus = true

            onTextChanged: {
                hints.model.clear();
                stationEsr = null;

                if (text.length > 2) {
                    var results = sqltoqml.getHints(text, currentZoneIndex);
                    for (var i in results) {
                        hints.model.append(results[i]);
                        console.log(results[i].esr);
                    }
                }
            }

            onFocusChanged: {
                console.log("Focus changed!");
                if (!focus) {
                    hints.model.clear();
                } else {
                    searchField.onTextChanged();
                }
            }
        }

        IconButton{
            id: locateFrom
            anchors.verticalCenter: parent.verticalCenter
            //onClicked: whereFrom()
            icon.source:
                "image://theme/icon-m-whereami"
        }
    }

    SilicaListView {
        id: hints
        width: parent.width
        height: count ? contentHeight : 0

        model: ListModel {}

        delegate: BackgroundItem {
            id: listItem
            width: parent.width
            height: Theme.itemSizeExtraSmall
            property var esrId: esr

            Label {
                id: hintLabel
                anchors.fill: parent
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                font.pixelSize: Theme.fontSizeSmall
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                verticalAlignment: Text.AlignVCenter
                truncationMode: TruncationMode.Fade
                text: title
            }

            onClicked: {
                searchField.text = title;
                stationEsr = esrId;
                hints.model.clear();
            }
        }
    }
}
