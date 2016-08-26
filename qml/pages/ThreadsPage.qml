import QtQuick 2.0
import Sailfish.Silica 1.0
import subtrains 1.0

Page {
    id: page
    property QmlHandler qmlHandler

    BusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
        running: true
    }

    Connections {
        target: qmlHandler
        onThreadsListRecieved: {
            busyIndicator.running = false;
            viewPlaceholder.text =
                    qsTr("Не нашлось подходящих маршрутов :(");
        }
        onErrorRecievingThreads: {
            busyIndicator.running = false;
            viewPlaceholder.text =
                    qsTr("Что-то пошло не так. " +
                    "Пожалуйста, проверьте, что у вас включена " +
                    "передача данных " +
                    "и попробуйте снова");
        }
    }

    SilicaListView {
        //    ListView {
        id: listView
        model: qmlHandler.routeModel
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Маршруты по направлению")
        }
        ViewPlaceholder {
            id: viewPlaceholder
            enabled: listView.count == 0 && !busyIndicator.running
            text: ""
        }
        delegate: ListItem {
            id: delegate
            contentHeight: Theme.itemSizeLarge
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
            }
            Column {
                id: leftColumn
                anchors.left: parent.left
                Label {
                    id: departureTime
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    text: modelData.departure.substring(11,16)
                }
                Label {
                    id: arrivalTime
                    anchors.horizontalCenter: leftColumn.horizontalCenter
                    font.pixelSize: Theme.fontSizeMedium
                    text: modelData.arrival.substring(11,16)
                }
            }
            Label {
                id: centerLabel
                anchors {
                    left: leftColumn.right
                    right: rightColumn.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: Theme.paddingLarge
                    rightMargin: Theme.paddingLarge
                }
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.WordWrap
                text: modelData.thread.title

            }
            Column {
                id: rightColumn
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    id: duration
                    text: modelData.duration / 60 + qsTr(" мин.")
                }

            }
            onClicked: {
                qmlHandler.getTrainInfo(modelData.thread.uid, new Date(modelData.departure));
                pageStack.push(Qt.resolvedUrl("ThreadInfo.qml"), {qmlHandler: qmlHandler});
            }
        }
        VerticalScrollDecorator{}
    }
}

