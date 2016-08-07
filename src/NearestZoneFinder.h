#ifndef NEARESTZONEFINDER_H
#define NEARESTZONEFINDER_H

#include <QGeoCoordinate>
#include "SearchHint.h"

class NearestZoneFinder
{
public:
    static SearchHint* findNearestZone(const QGeoCoordinate& coordinate);
    static SearchHint* getZoneById(const int zone);
};

#endif // NEARESTZONEFINDER_H
