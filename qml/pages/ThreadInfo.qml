import QtQuick 2.0
import Sailfish.Silica 1.0
import firsttry 1.0

Page
{
    property QmlHandler qmlHandler;

    Label {
        text: qmlHandler.trainInfoModel.title
    }
}
