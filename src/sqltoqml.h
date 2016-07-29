#ifndef SQLTOQML_H
#define SQLTOQML_H

#include <QObject>
#include <QtSql/QtSql>
#include "searchhint.h"

class SQLtoQML : public QObject
{
    Q_OBJECT
public:
    SQLtoQML(QObject *parent = 0);
    Q_INVOKABLE QList<QObject*> getHints(QString text, int zone);

signals:

public slots:

};

#endif // SQLTOQML_H
