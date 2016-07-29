#include "NearestZoneFinder.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

void NearestZoneFinder::findNearestZone(const QGeoCoordinate &coordinate)
{
    QSqlQuery query;

    query.prepare("select zone, latitude, longitude from settlement");
    query.exec();

    QSqlRecord record = query.record();

    int zone = -1;
    qreal distance = 0;

    while (query.next()) {
        int curzone = query.value("zone").toInt();
        double latitude = query.value("latitude").toDouble();
        double longitude = query.value("longitude").toDouble();

        QGeoCoordinate current(latitude, longitude);

        if (zone == -1) {
            zone = curzone;
            distance = current.distanceTo(coordinate);
        } else if (current.distanceTo(coordinate) < distance) {
            distance = current.distanceTo(coordinate);
            zone = curzone;
        }
    }
}

SearchHint NearestZoneFinder::getZoneById(const int zone)
{
    QSqlQuery query;

    query.prepare("select settlement_title from zone where id = :id");
    query.bindValue(":id", zone);
    query.exec();

    query.next();
    return SearchHint(query.value("settlement_title").toString(), zone);
}

