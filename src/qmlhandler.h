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
public:
    explicit QmlHandler(QObject *parent = 0);

    Q_INVOKABLE void getRoute(QString originStation, QString destStation, QDate tripDate);

    void setRouteModel(const QList<Thread*> newRtModel)
    {
        m_routeModel = newRtModel;
        emit routeModelChanged();
    }

    QQmlListProperty<Thread> routeModel()
    {
        return QQmlListProperty<Thread>(this, m_routeModel);
    }
signals:
    void routeModelChanged();
public slots:
    void onGetRouteFinished(QNetworkReply* netReply);
private:
    QList<Thread*> m_routeModel;
};

#endif // QMLHANDLER_H
