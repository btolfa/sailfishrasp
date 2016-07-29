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

class PosRequest : public QObject
{
    Q_OBJECT
public:
    explicit PosRequest(QObject *parent = 0);

signals:

public slots:
    void requestFinished(QNetworkReply *reply);
    void positionUpdated(const QGeoPositionInfo &info);
private:
    void getNearestStations(const QGeoPositionInfo &info);
    void parseResponce(const QJsonDocument& document);

    QString apikey;
    QScopedPointer<QGeoPositionInfoSource> source;
    QScopedPointer<QNetworkAccessManager> nam;
};

#endif // POSREQUEST_H
