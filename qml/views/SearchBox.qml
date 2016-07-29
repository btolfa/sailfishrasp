import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: searchColumn
    property alias placeHolderText: searchField.placeholderText
    height: searchRow.height + hints.height
    width: parent.width

    signal changeFocus(bool focusState)

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
            EnterKey.enabled: hints.count > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                var item = hints.model.get(0);

                if (item) {
                    stationEsr = item.esr;
                    searchField.text = item.title;
                }

                hints.model.clear();

                focus = false;
                activeFocus = false;
                changeFocus(false);
            }

            onTextChanged: {
                hints.model.clear();
                stationEsr = null;

                if (text.length > 2) {
                    var results = sqltoqml.getHints(text, 1);
                    for (var i in results) {
                        hints.model.append(results[i]);
                        console.log(results[i].esr);
                    }
                }
            }

            onActiveFocusChanged: {
                changeFocus(activeFocus);

                if (!activeFocus) {
                    var item = hints.model.get(0);
                    console.log(item);
                    if (item) {
                        stationEsr = item.esr;
                        searchField.text = item.title;
                    }

                    hints.model.clear();
                } else {
                    searchField.textChanged();
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
