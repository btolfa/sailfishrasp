#ifndef POSREQUEST_H
#define POSREQUEST_H

#include <QObject>
#include <QGeoPositionInfo>
#include <QNetworkReply>
#include <QScopedPointer>
#include <QGeoPositionInfoSource>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>
#include "searchhint.h"

class PosRequest : public QObject
{
    Q_OBJECT
    Q_PROPERTY (SearchHint* currentZone READ currentZone NOTIFY currentZoneReady)
    Q_PROPERTY (SearchHint* currentZoneUser WRITE setCurrentZone READ currentZoneUser NOTIFY currentZoneUserChanged)
public:
    explicit PosRequest(QObject *parent = 0);

    SearchHint* currentZone() {
        return _currentZone;
    }

    SearchHint* currentZoneUser() {
        return _currentZone;
    }

    void setCurrentZone(SearchHint* zone) {
        _currentZone = zone;

        emit currentZoneUserChanged();
    }

signals:
    void currentZoneReady();
    void currentZoneUserChanged();
public slots:
    void requestFinished(QNetworkReply *reply);
    void positionUpdated(const QGeoPositionInfo &info);
private:
    void getNearestStations(const QGeoPositionInfo &info);
    void parseResponce(const QJsonDocument& document);

    SearchHint* _currentZone;

    QScopedPointer<QGeoPositionInfoSource> source;
    QScopedPointer<QNetworkAccessManager> nam;
};

#endif // POSREQUEST_H
