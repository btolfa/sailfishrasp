#ifndef POSREQUEST_H
#define POSREQUEST_H

#include <QObject>

class PosRequest : public QObject
{
    Q_OBJECT
public:
    explicit PosRequest(QObject *parent = 0);

signals:

public slots:
};

#endif // POSREQUEST_H
