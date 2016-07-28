#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML(QObject *parent) : QObject(parent)
{
    getHints();
}

QList<QObject*> SQLtoQML::getHints()
{
    loaddb();
    QSqlQuery query;
    QSqlRecord rec = query.record();
    query.exec("SELECT * from zone");
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
