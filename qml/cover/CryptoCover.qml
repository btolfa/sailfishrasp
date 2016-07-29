import QtQuick 2.0
import Sailfish.Silica 1.0
import firsttry 1.0

CoverPage{
    Label{
        text: "Ближайшая электричка:\n"+qmlHandler.routeModel.Count
    }
}

