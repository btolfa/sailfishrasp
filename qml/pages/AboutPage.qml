import QtQuick 2.0
import Sailfish.Silica 1.0
import subtrains 1.0

Page {
    Column {
        anchors.fill: parent
        spacing: Theme.paddingMedium

        PageHeader {
            id: header
            title: qsTr("PAGES.ABOUT")
        }

        DetailItem {
            id: authors
            label: qsTr("Авторы")
            value: qsTr("Евгений Файвужинский,
Тенгиз Шарафиев,
Алексей Бедник,
Артём Рапопорт,
Никита Ухрёнков,
Дмитрий Бычков")
        }

        BackgroundItem{
            width: parent.width
            height: copyr.height
            onClicked: {console.log(Qt.locale()); Qt.openUrlExternally("http://rasp.yandex.ru/");}
            Image {
                id: copyr
                source: "copyright.svg"
                sourceSize.width: parent.width * 0.8
                sourceSize.height: height
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
