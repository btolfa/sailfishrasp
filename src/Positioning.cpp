#include "Positioning.h"

#include "NearestZoneFinder.h"

Positioning::Positioning(QObject *parent)
    : QObject(parent)
    , source(QGeoPositionInfoSource::createDefaultSource(parent))
{
    connect(source.data(), SIGNAL(positionUpdated(QGeoPositionInfo)),
                        this, SLOT(positionUpdated(QGeoPositionInfo)));
    source->startUpdates();
}

void Positioning::positionUpdated(const QGeoPositionInfo &info)
{
    source->stopUpdates();
    _currentZone = NearestZoneFinder::findNearestZone(info.coordinate());
    emit currentZoneReady();
}

