import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    spacing: Theme.paddingSmall
    width: parent.width
    property alias placeHolderText: searchField.placeholderText

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
    }
}
