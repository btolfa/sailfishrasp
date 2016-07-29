#include "sqltoqml.h"
#include <QtSql/QtSql>
#include "sailfishapp.h"

SQLtoQML::SQLtoQML(QObject *parent) : QObject(parent)
{
    qDebug() << "INIT SQLtoQML";
    loaddb();
}

QList<QObject*> SQLtoQML::getHints(QString text, int zone)
{
    QSqlQuery query;

    query.prepare("SELECT title, esr FROM station "
                  "WHERE zone=:zone AND UPPER(title) LIKE :title "
                  "ORDER BY importance, title LIMIT 5; ");
    query.bindValue(":title", text.toUpper() + "%");
    query.bindValue(":zone", zone);
    if (!query.exec()) {
        qDebug() << "SQL query error: " << query.lastError().text();
    }

    QSqlRecord rec = query.record();
    QList<QObject*> hints;

    while (query.next()) {
        int esr = query.value(rec.indexOf("esr")).toInt();
        QString title = query.value(rec.indexOf("title")).toString();
        hints.append(new SearchHint(title, esr));
    }

    return hints;
}

void SQLtoQML::loaddb()
{
   sdb = QSqlDatabase::addDatabase("QSQLITE");
   QUrl dbPath = SailfishApp::pathTo("db/rasp.sqlite");
  // qDebug() << SailfishApp::pathTo("db/rasp.sqlite").path();
   sdb.setDatabaseName(dbPath.path());
    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }else{
        qDebug() << "sql LOADED";
    }
}
