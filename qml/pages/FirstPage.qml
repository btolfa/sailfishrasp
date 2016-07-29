/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import firsttry 1.0
import "../views"
import "Util.js" as Util
import org.crypt.rasp 1.0

Page {
    id: page
    property var zoneId

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        VerticalScrollDecorator {}

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Сменить пригородную зону")
                onClicked: { var dialog = pageStack.push(Qt.resolvedUrl("ZonePage.qml"));
                    dialog.accepted.connect(function(id, text) {
                        page.zoneId = id;
                        currentZone.value = text;
                    })
                }
            }
        }

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.

        SQLtoQML {
            id: sqltoqml
        }

<<<<<<< Updated upstream
        PosRequest {
            id: posRequest

            onCurrentZoneReady: {
                currentZone.value = posRequest.currentZone.title
                searchFrom.currentZoneIndex = posRequest.currentZone.esr
                searchTo.currentZoneIndex = posRequest.currentZone.esr
            }
        }
=======
        //        PosRequest {
        //            id: posRequest
        //        }
>>>>>>> Stashed changes

        Column {
            id: column

            anchors.fill: parent
            spacing: Theme.paddingMedium

            // ЗАГОЛОВОК

            PageHeader {
                title: qsTr("Расписание электричек")
                id: pageHeader
            }

            DetailItem {
                id: currentZone
                label: qsTr("Регион")
                value: qsTr("Москва и область")
            }

            // ДАТА

            BackgroundItem {
                id: button
                width: parent.width
                height: Theme.itemSizeLarge
                //                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    var currentDate = new Date();
                    var dateForCalendar = dateLabel.areSelectedAndCurrentDateEqual() === true ?
                                currentDate :
                                dateLabel.selectedDate;
                    var dialog = pageStack.push(pickerComponent, {
                                                    date: dateForCalendar
                                                })
                    dialog.accepted.connect(function() {
                        dateLabel.selectedDate = dialog.date;
                        dateLabel.text = Util.formatDateWeekday(dialog.date);
                        var isEarlierDate = false;
                        if (dialog.date.getFullYear() < currentDate.getFullYear) {
                            isEarlierDate = true;
                        }
                        else if (dialog.date.getMonth() < currentDate.getMonth) {
                            isEarlierDate = true;
                        }
                        else if (dialog.date.getDate() < currentDate.getDate()) {
                            isEarlierDate = true;
                        }
                        badDate.visible = isEarlierDate;
                    })
                }

                Label {
                    id: dateLabel
                    anchors {
                        right: moreImage.left
                        rightMargin: Theme.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }
                    property var selectedDate: {return null}
                    property var areSelectedAndCurrentDateEqual: {
                        function() {
                            var currentDate = new Date();
                            if (dateLabel.selectedDate.getDate() !== currentDate.getDate() ||
                                    dateLabel.selectedDate.getMonth() !== currentDate.getMonth() ||
                                    dateLabel.selectedDate.getFullYear() !== currentDate.getFullYear()) {
                                return false;
                            }
                            return true;
                        }
                    }
                    text: {var currentDate = new Date();
                        dateLabel.selectedDate = currentDate;
                        return Util.formatDateWeekday(currentDate)}
                    color: button.highlighted ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeLarge
                }

                Image {
                    id: moreImage
                    anchors {
                        right: parent.right
                        rightMargin: Theme.horizontalPageMargin + Theme.paddingSmall
                        verticalCenter: parent.verticalCenter
                    }
                    source: "image://theme/icon-m-right?" + (button.highlighted ? Theme.highlightColor
                                                                                : Theme.primaryColor)
                }

                Component {
                    id: pickerComponent
                    DatePickerDialog {}
                }
            }

            // ПЛОХАЯ ДАТА

            SectionHeader {
                id: badDate
                visible: false
                //                color: "red"
                text: qsTr("Выбрана прошедшая дата")
            }

            // ОТКУДА

            SearchBox {
                id: searchFrom
                zoneId: page.zoneId
                placeHolderText: qsTr("Откуда")
                onChangeFocus: {
                    console.log("Got focus signal");

                    pageHeader.visible = !focusState;
                    currentZone.visible = !focusState;
                    button.visible = !focusState;
                    // Handle badDate somehow
                    searchTo.visible = !focusState;
                }
            }

            // КУДА

            SearchBox {
                id: searchTo
                zoneId: page.zoneId
                placeHolderText: qsTr("Куда")

                onChangeFocus: {
                    console.log("Got focus signal");

                    pageHeader.visible = !focusState;
                    currentZone.visible = !focusState;
                    button.visible = !focusState;
                    // Handle badDate somehow
                    searchFrom.visible = !focusState;
                }
            }

            // ВРЕМЕННАЯ КНОПКА

            Button {
                //enabled: searchFrom.stationEsr && searchTo.stationEsr
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Поиск")
                onClicked: {
                    console.log(searchFrom.stationEsr, searchTo.stationEsr);
                    qmlHandler.getRoute(searchFrom.stationEsr, searchTo.stationEsr, dateLabel.selectedDate);
                    pageStack.push(Qt.resolvedUrl("ThreadsPage.qml"), {qmlHandler: qmlHandler});
                }
            }
        }
    }
}
