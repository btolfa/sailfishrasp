#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML()
{

}

QList<QObject*> SQLtoQML::getHints()
{

}

void SQLtoQML::loaddb()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("rasp");
    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }
}
