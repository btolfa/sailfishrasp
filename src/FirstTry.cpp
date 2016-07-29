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

#include <QtQuick>

#include <sailfishapp.h>
#include <QQuickView>
#include <QGuiApplication>
#include <QQmlContext>
#include <QSqlDatabase>


#include "qmlhandler.h"
#include "sqltoqml.h"
#include "PosRequest.h"
#include "searchhint.h"


QSqlDatabase loadDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(SailfishApp::pathTo("db/rasp.sqlite").path());
    if (! db.open()) {
        qDebug() << db.lastError().text();
    }

    return db;
}

int main(int argc, char *argv[])
{
    QGuiApplication * sailfishRaspApp = SailfishApp::application(argc, argv);
    sailfishRaspApp -> setApplicationName("TimeToSail");
    sailfishRaspApp -> setOrganizationName("SixTiredGuys");

    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QSqlDatabase db = loadDb();

    qmlRegisterType<QmlHandler>("firsttry", 1, 0, "QmlHandler");
    qmlRegisterType<SQLtoQML>("org.crypt.rasp", 1, 0, "SQLtoQML");
    qmlRegisterType<PosRequest>("org.crypt.rasp", 1, 0, "PosRequest");
    qmlRegisterType<SearchHint>("org.crypt.rasp", 1, 0, "SearchHint");

    QQuickView* qView = SailfishApp::createView();
    qView->setSource(SailfishApp::pathTo("qml/FirstTry.qml"));
    qView->show();

    return sailfishRaspApp -> exec();
}

