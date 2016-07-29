import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    property alias placeHolderText: searchField.placeholderText
    height: searchRow.height + hints.height
    width: parent.width

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
                if (text.length > 2) {
                    hints.model.clear();

                    var results = sqltoqml.getHints(text, 1);
                    for (var i in results) {
                        hints.model.append(results[i]);
                    }
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
        height: contentHeight

        model: ListModel {}

        delegate: BackgroundItem {
            id: listItem
            width: parent.width
            height: Theme.itemSizeExtraSmall

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
                hints.model.clear();
            }
        }
    }
}
