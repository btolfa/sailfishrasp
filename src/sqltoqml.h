#ifndef SQLTOQML_H
#define SQLTOQML_H

#include <QObject>
#include <QtSql/QtSql>
#include "searchhint.h"

class SQLtoQML
{
public:
    SQLtoQML();
    QList<QObject*> getHints();
signals:

private:
    void loaddb();
    QSqlDatabase sdb;
public slots:

};

#endif // SQLTOQML_H
