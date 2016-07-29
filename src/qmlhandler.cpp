#include "qmlhandler.h"

QmlHandler::QmlHandler(QObject *parent) : QObject(parent)
{
    qDebug()<<"\n-----New qml handler created\n";
}

void QmlHandler::setRouteModel(const QList<Thread*> newRtModel)
{
    m_routeModel = newRtModel;
    emit routeModelChanged();
}

void QmlHandler::getTrainInfo(QString threadId, QDate tripDate)
{
    qDebug()<<"Get train Info: "+threadId+" "+tripDate.toString();

    QNetworkAccessManager* m_pNetAccessMngr =
                                 new QNetworkAccessManager(this);

    QUrl reqUrl = QUrl("https://api.rasp.yandex.net/v1.0/thread/");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("apikey","20e7cb3e-6b05-4774-bcbb-4b0fb74a58b0");
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
    QList<Thread*> dataList; //будущая модель

    if (netReply != NULL &&
            netReply->bytesAvailable() > 0 &&
            netReply->error() == QNetworkReply::NoError)
    {
        QString replyStr = netReply->readAll();

        qDebug()<<"\n Success getting trains!";

        QJsonDocument jsonResponse = QJsonDocument::fromJson(replyStr.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["threads"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            dataList.append(new Thread(obj));
        }

        setRouteModel(dataList);
    }
}

void QmlHandler::onGetTrainInfoFinished(QNetworkReply* netReply)
{
    if(netReply != NULL
            && netReply->bytesAvailable() > 0
            && netReply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"\n Success getting threadInfo!";

        m_trainInfoModel = QJsonDocument::fromJson(
                    ((QString)netReply->readAll())
                    .toUtf8()).toVariant();

        emit trainInfoModelChanged();
    }
}
