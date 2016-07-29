#ifndef NEARESTZONEFINDER_H
#define NEARESTZONEFINDER_H

#include <QGeoCoordinate>

class NearestZoneFinder
{
public:
    static void findNearestZone(const QGeoCoordinate& coordinate);
};

#endif // NEARESTZONEFINDER_H
