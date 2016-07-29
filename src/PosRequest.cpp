#include "PosRequest.h"
#include <QDebug>
#include <QUrlQuery>
#include <QJsonArray>

PosRequest::PosRequest(QObject *parent)
    : QObject(parent)
    , apikey("20e7cb3e-6b05-4774-bcbb-4b0fb74a58b0")
    , source(QGeoPositionInfoSource::createDefaultSource(parent))
    , nam(new QNetworkAccessManager())
{
    connect(source.data(), SIGNAL(positionUpdated(QGeoPositionInfo)),
                        this, SLOT(positionUpdated(QGeoPositionInfo)));
    source->startUpdates();

    connect(nam.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

void PosRequest::requestFinished(QNetworkReply *reply)
{
    parseResponce(QJsonDocument::fromJson(reply->readAll()));
}

void PosRequest::positionUpdated(const QGeoPositionInfo &info)
{
    source->stopUpdates();
    getNearestStations(info);
}

void PosRequest::getNearestStations(const QGeoPositionInfo &info)
{
    QUrl url = QUrl("https://api.rasp.yandex.net/v1.0/nearest_stations/");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("apikey", "20e7cb3e-6b05-4774-bcbb-4b0fb74a58b0");
    urlQuery.addQueryItem("format", "json");
    urlQuery.addQueryItem("lat", QString("%1").arg(info.coordinate().latitude()));
    urlQuery.addQueryItem("lng", QString("%1").arg(info.coordinate().longitude()));
    urlQuery.addQueryItem("distance", QString("%1").arg(50));
    urlQuery.addQueryItem("lang", "ru");
    urlQuery.addQueryItem("transport_types", "train");
    url.setQuery(urlQuery);

    QNetworkRequest request;
    request.setUrl(url);
    nam->get(request);
}

void PosRequest::parseResponce(const QJsonDocument& document)
{
    QJsonArray stations = document.object()["stations"].toArray();
}

