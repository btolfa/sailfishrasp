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
public:
    explicit PosRequest(QObject *parent = 0);

    SearchHint* currentZone() {
        return _currentZone;
    }

signals:
    void currentZoneReady();
public slots:
    void requestFinished(QNetworkReply *reply);
    void positionUpdated(const QGeoPositionInfo &info);
private:
    void getNearestStations(const QGeoPositionInfo &info);
    void parseResponce(const QJsonDocument& document);

    SearchHint* _currentZone;

    QString apikey;
    QScopedPointer<QGeoPositionInfoSource> source;
    QScopedPointer<QNetworkAccessManager> nam;
};

#endif // POSREQUEST_H
