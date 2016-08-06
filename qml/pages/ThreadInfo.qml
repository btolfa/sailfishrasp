import QtQuick 2.0
import Sailfish.Silica 1.0
import subtrains 1.0

Page
{
    property QmlHandler qmlHandler;
    SilicaListView {
        id: sListView
        model: qmlHandler.trainInfoModel.stops
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Маршруты по направлению")
        }
        delegate: ListItem {
            id: delegate
            property int indexOfThisDelegate: index
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
                topMargin: 0
                bottomMargin: 0
            }
            Image {
                id: image
                source:
                    if (index === 0)
                    {"line-top.svg"}
                    else {
                        if (index === sListView.count-1)
                        {"line-bot.svg"}
                        else
                        {
                            if (!modelData.stop_time)
                            {"line-grey.svg"}
                            else {
                            "line-med.svg"}
                    }}

                        width: 100
                        height: 100
                        sourceSize.width: width
                        sourceSize.height: height
                    }

                Label {
                    anchors.left: image.right
                    anchors.right: time.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: Theme.paddingMedium
                    text: modelData.station.title
//                    elide: Text.ElideRight
                    truncationMode: TruncationMode.Fade
                    color: if (!modelData.stop_time && index !== 0 && index !== sListView.count-1)
                           {Theme.secondaryColor} else
                           {Theme.primaryColor}
                }

                Label {
                    id: time
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text:
                        if (!modelData.stop_time && index !== 0 && index !== sListView.count-1)
                          {""} else {modelData.departure.substring(11,16)}
                    font.bold: true
                }
            }
            VerticalScrollDecorator{}
        }
    }
