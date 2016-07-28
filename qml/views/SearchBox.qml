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
            //            validator: DoubleValidator {
            //                bottom: -1
            //                top: 10
            //                decimals: 2
            //            }
            //            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        IconButton{
            id: locateFrom
            anchors.verticalCenter: parent.verticalCenter
            //onClicked: whereFrom()
            icon.source:
                "image://theme/icon-m-whereami"

            onClicked: {
                hints.model.clear()
                var i
                for (i = 0; i <= 4; i++) {
                    hints.model.append({ hint: "тест" });
                }
            }
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
                text: hint
            }
        }
    }
}
