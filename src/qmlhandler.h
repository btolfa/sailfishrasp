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
#include "thread.h"

class QmlHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QQmlListProperty<Thread> routeModel READ routeModel NOTIFY routeModelChanged)
    Q_PROPERTY (QVariant trainInfoModel READ trainInfoModel NOTIFY trainInfoModelChanged)
public:
    explicit QmlHandler(QObject *parent = 0);

    Q_INVOKABLE void getRoute(QString originStation, QString destStation, QDate tripDate);
    Q_INVOKABLE void getTrainInfo(QString threadId, QDate tripDate);

    QQmlListProperty<Thread> routeModel()
    {
        return QQmlListProperty<Thread>(this, m_routeModel);
    }

    QVariant trainInfoModel()
    {
        return m_trainInfoModel;
    }
signals:
    void routeModelChanged();
    void trainInfoModelChanged();
public slots:
    void onGetRouteFinished(QNetworkReply* netReply);
    void onGetTrainInfoFinished(QNetworkReply* netReply);
private:
    QList<Thread*> m_routeModel;
    QVariant m_trainInfoModel;

    void setRouteModel(const QList<Thread*> newRtModel);
};

#endif // QMLHANDLER_H
