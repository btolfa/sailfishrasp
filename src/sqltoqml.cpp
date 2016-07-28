#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML(QObject *parent) : QObject(parent)
{
    loaddb();
}

QList<QObject*> SQLtoQML::getHints()
{
    QSqlQuery query;
    query.exec("SELECT * FROM settlement");
    qDebug() << query.result();
}

void SQLtoQML::loaddb()
{
   sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("rasp.sqlite");
    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }
    getHints();
}
