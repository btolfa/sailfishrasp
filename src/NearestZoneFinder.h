#ifndef NEARESTZONEFINDER_H
#define NEARESTZONEFINDER_H

#include <QGeoCoordinate>
#include "searchhint.h"

class NearestZoneFinder
{
public:
    static void findNearestZone(const QGeoCoordinate& coordinate);
    static SearchHint getZoneById(const int zone);
};

#endif // NEARESTZONEFINDER_H
