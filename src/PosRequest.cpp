#include "PosRequest.h"

#include "NearestZoneFinder.h"

PosRequest::PosRequest(QObject *parent)
    : QObject(parent)
    , source(QGeoPositionInfoSource::createDefaultSource(parent))
{
    connect(source.data(), SIGNAL(positionUpdated(QGeoPositionInfo)),
                        this, SLOT(positionUpdated(QGeoPositionInfo)));
    source->startUpdates();
}

void PosRequest::positionUpdated(const QGeoPositionInfo &info)
{
    source->stopUpdates();
    _currentZone = NearestZoneFinder::findNearestZone(info.coordinate());
    emit currentZoneReady();
}

