#ifndef NEARESTZONEFINDER_H
#define NEARESTZONEFINDER_H

#include <QObject>

class NearestZoneFinder : public QObject
{
    Q_OBJECT
public:
    explicit NearestZoneFinder(QObject *parent = 0);

signals:

public slots:
};

#endif // NEARESTZONEFINDER_H
