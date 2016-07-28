#include "sqltoqml.h"
#include <QtSql/QtSql>

SQLtoQML::SQLtoQML()
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
