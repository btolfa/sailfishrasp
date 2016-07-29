#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML(QObject *parent) : QObject(parent)
{
    loaddb();
    getHints("МОС", 1);
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
    sdb.setDatabaseName("/usr/share/FirstTry/db/rasp.sqlite");
    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }else{
        qDebug() << "sql LOADED";
    }
}
