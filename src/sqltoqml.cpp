#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML(QObject *parent) : QObject(parent)
{
}

QList<QObject*> SQLtoQML::getHints()
{
    QSqlQuery query;
    if (!query.exec("SELECT * from zone LIMIT 1;")) {
        qDebug() << "SQL query error: " << query.lastError().text();
    }

    QSqlRecord rec = query.record();

    while (query.next()) {
        int geo = query.value(rec.indexOf("id")).toInt();
        qDebug() << "number is " << geo;
    }
   // qDebug() << query.lastError();
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
