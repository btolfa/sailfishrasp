#include "PosRequest.h"

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
}

void PosRequest::positionUpdated(const QGeoPositionInfo &info)
{

}

void PosRequest::getNearestStations(const QGeoPositionInfo &info)
{

}

void PosRequest::parseResponce(const QJsonDocument document)
{

}

