#include "sqlite.h"
#include <QtSql/QtSql>

SQLite::SQLite()
{

}

void SQLite::cretebd()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("db_name.sqlite");
}



