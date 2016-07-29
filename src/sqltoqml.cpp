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

    query.prepare("SELECT title,esr from station WHERE upper(title) LIKE :title AND zone=:zone ORDER BY importance, title LIMIT 5; ");
    query.bindValue(":title", text.toUpper() + "%");
    query.bindValue(":zone", zone);
    if (!query.exec()) {
        qDebug() << "SQL query error: " << query.lastError().text();
    }

    QSqlRecord rec = query.record();
    QList<SearchHint*> hints;

    while (query.next()) {
        int esr = query.value(rec.indexOf("esr")).toInt();
        QString title = query.value(rec.indexOf("title")).toString();
        qDebug()  << title << esr;
        hints.append(new SearchHint(title, esr));
    }
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
