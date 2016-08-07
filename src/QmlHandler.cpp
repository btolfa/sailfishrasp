#include "QmlHandler.h"
#include "OurResource.h"

QmlHandler::QmlHandler(QObject *parent) : QObject(parent)
{
}

void QmlHandler::setRouteModel(const QJsonArray newRtModel)
{
    m_routeModel = newRtModel;
    emit routeModelChanged();
}

void QmlHandler::getTrainInfo(QString threadId, QDate tripDate)
{

    QNetworkAccessManager* m_pNetAccessMngr =
                                 new QNetworkAccessManager(this);

    QUrl reqUrl = QUrl("https://api.rasp.yandex.net/v1.0/thread/");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("apikey", OurResource::getApiKey());
    urlQuery.addQueryItem("format","json");
    urlQuery.addQueryItem("lang","ru");
    urlQuery.addQueryItem("uid", threadId);
    urlQuery.addQueryItem("date",tripDate.toString("yyyy-MM-dd"));

    reqUrl.setQuery(urlQuery);

    QNetworkRequest request = QNetworkRequest();
    request.setUrl(reqUrl);

    bool res;
    Q_UNUSED(res);

    res = connect(m_pNetAccessMngr,
                  SIGNAL(finished(QNetworkReply*)),
                  this,
                  SLOT(onGetTrainInfoFinished(QNetworkReply*)));
    Q_ASSERT(res);

    m_pNetAccessMngr->get(request);
}


void QmlHandler::getRoute(QString originStation, QString destStation, QDate tripDate)
{
    QNetworkAccessManager* m_pNetAccessMngr =
                                 new QNetworkAccessManager(this);

    QUrl reqUrl = QUrl("https://api.rasp.yandex.net/v1.0/search/");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("apikey", OurResource::getApiKey());
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
    QVariantList dataList;

    if (netReply != NULL &&
            netReply->bytesAvailable() > 0 &&
            netReply->error() == QNetworkReply::NoError)
    {
        QString replyStr = netReply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(replyStr.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["threads"].toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            QJsonObject obj = jsonArray.at(i).toObject();
            obj.insert("hasAlreadyLeft",
                       (QDateTime::currentDateTime() >=
                        QDateTime::fromString(obj.value("departure").toString())));

            jsonArray.replace(i, obj);
        }

        setRouteModel(jsonArray);

        emit threadsListRecieved();
    }
    else
    {
        emit errorRecievingThreads();
    }
}

void QmlHandler::onGetTrainInfoFinished(QNetworkReply* netReply)
{
    if(netReply != NULL
            && netReply->bytesAvailable() > 0
            && netReply->error() == QNetworkReply::NoError)
    {

        m_trainInfoModel = QJsonDocument::fromJson(
                    ((QString)netReply->readAll())
                    .toUtf8()).toVariant();

        emit trainInfoModelChanged();
    }
}

QList<QObject*> QmlHandler::getStationHints(QString text, int zone)
{
    QSqlQuery query;

    query.prepare("SELECT title, esr FROM station "
                  "WHERE "
                  "zone=:zone AND "
                  "(UPPER(title) LIKE :title "
                  "OR UPPER(popular_title) LIKE :title "
                  "OR UPPER(short_title) LIKE :title "
                  ") "
                  "ORDER BY importance, title LIMIT 5; ");
    query.bindValue(":title", text.toUpper() + "%");
    query.bindValue(":zone", zone);
    if (!query.exec()) {
        qDebug() << "SQL query error: " << query.lastError().text();
    }

    QSqlRecord rec = query.record();
    QList<QObject*> hints;

    while (query.next()) {
        int esr = query.value(rec.indexOf("esr")).toInt();
        QString title = query.value(rec.indexOf("title")).toString();
        hints.append(new SearchHint(title, esr));
    }

    return hints;
}

QList<QObject *> QmlHandler::getZonesLike(QString text)
{
    QSqlQuery query;

    query.prepare("select id, settlement_title from zone "
                  "where settlement_title LIKE :settlement_title "
                  "order by settlement_title ASC");
    query.bindValue(":settlement_title", text.toUpper() + "%");
    query.exec();

    QList<QObject*> zones;
    while (query.next()) {
        zones.append(new SearchHint(
                             query.value("settlement_title").toString()
                           , query.value("id").toInt()
                         ));
    }

    return zones;
}

QList<QObject *> QmlHandler::getAllZones()
{
    QSqlQuery query;

    query.exec("select id, settlement_title from zone "
                  "order by settlement_title ASC");

    QList<QObject*> zones;
    while (query.next()) {
        zones.append(new SearchHint(
                             query.value("settlement_title").toString()
                           , query.value("id").toInt()
                         ));
    }

    return zones;
}
