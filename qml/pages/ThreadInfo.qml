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
            title: qsTr("Интервалы остановок")
        }
        delegate: ListItem {
            id: delegate
            property int indexOfThisDelegate: index
            height: Theme.itemSizeMedium
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

                width: Theme.itemSizeMedium
                height: Theme.itemSizeMedium
                sourceSize.width: width
                sourceSize.height: height
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                anchors.left: image.right
                anchors.right: time.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: Theme.paddingMedium
                text: modelData.station.title
                truncationMode: TruncationMode.Fade
                color: if (!modelData.stop_time && index !== 0 && index !== sListView.count-1)
                       {Theme.secondaryColor} else
                       {Theme.primaryColor}
            }

            Label {
                id: time
                width: 90
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                text: {
                    var resultText = "";
                    if (modelData.stop_time || index === 0 || index === sListView.count-1)
                    {
                        // if (modelData.arrival === "" || modelData.departure === "")

                        resultText = ( (modelData.arrival ? modelData.arrival.substring(11, 16) : "")
                                      + (modelData.arrival ? modelData.departure ? " –\r\n" : "" : "" )
                                      + (modelData.departure ? modelData.departure.substring(11, 16) : "") );
                    }
                    return resultText;
                }
                font.bold: false
                horizontalAlignment: Text.AlignRight
            }
        }
        VerticalScrollDecorator{}
    }
}
