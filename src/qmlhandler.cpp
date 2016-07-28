#include "qmlhandler.h"

QmlHandler::QmlHandler(QObject *parent) : QObject(parent)
{

}

void QmlHandler::getRoute(QString originStation, QString destStation, QDate tripDate)
{
    QNetworkAccessManager* m_pNetAccessMngr =
                                 new QNetworkAccessManager(this);

    QUrl reqUrl = QUrl("https://api.rasp.yandex.net/v1.0/search/");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("apikey","20e7cb3e-6b05-4774-bcbb-4b0fb74a58b0");
    urlQuery.addQueryItem("format","json");
    urlQuery.addQueryItem("from",originStation);
    urlQuery.addQueryItem("to",destStation);
    urlQuery.addQueryItem("lang","ru");
    urlQuery.addQueryItem("system","esr");
    urlQuery.addQueryItem("date",tripDate.toString("yyyy-MM-dd"));

    reqUrl.setQuery(urlQuery);

    QNetworkRequest request = QNetworkRequest();
    request.setUrl(reqUrl);

    bool res;
    Q_UNUSED(res);

    res = connect(m_pNetAccessMngr,
                  SIGNAL(finished(QNetworkReply*)),
                  this,
                  SLOT(onGetRouteFinished(QNetworkReply*)));
    Q_ASSERT(res);

    m_pNetAccessMngr->get(request);
}

void QmlHandler::onGetRouteFinished(QNetworkReply *netReply)
{
    if (netReply != NULL &&
            netReply->bytesAvailable() > 0 &&
            netReply->error() == QNetworkReply::NoError)
    {
        QString replyStr = netReply->readAll();
        qDebug()<<replyStr;
    }
}

