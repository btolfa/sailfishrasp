#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>

class QmlHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY (QJsonArray routeModel READ routeModel NOTIFY routeModelChanged)
    Q_PROPERTY (QVariant trainInfoModel READ trainInfoModel NOTIFY trainInfoModelChanged)
    Q_PROPERTY (NOTIFY threadsListRecieved)
    Q_PROPERTY (NOTIFY errorRecievingThreads)
public:
    explicit QmlHandler(QObject *parent = 0);

    Q_INVOKABLE void getRoute(QString originStation, QString destStation, QDate tripDate);
    Q_INVOKABLE void getTrainInfo(QString threadId, QDate tripDate);

    QJsonArray routeModel()
    {
        return m_routeModel;
        //return QVariant(this, m_routeModel);
    }

    QVariant trainInfoModel()
    {
        return m_trainInfoModel;
    }
signals:
    void routeModelChanged();
    void trainInfoModelChanged();
    void threadsListRecieved();
    void errorRecievingThreads();
public slots:
    void onGetRouteFinished(QNetworkReply* netReply);
    void onGetTrainInfoFinished(QNetworkReply* netReply);
private:
    QJsonArray m_routeModel;
    QVariant m_trainInfoModel;

    void setRouteModel(const QJsonArray newRtModel);
};

#endif // QMLHANDLER_H
