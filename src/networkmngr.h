#ifndef NETWORKMNGR_H
#define NETWORKMNGR_H

#include <QObject>

class NetworkMngr : public QObject
{
    Q_OBJECT
public:
    explicit NetworkMngr(QObject *parent = 0);

    Q_INVOKABLE QList<QObject*> getRoute(QInt originStation, QInt destStation, QDate tripDate);
signals:

public slots:
};

#endif // NETWORKMNGR_H
