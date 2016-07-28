#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

class QmlHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QList<QObject*> routeModel READ routeModel WRITE setRouteModel NOTIFY routeModelChanged)
public:
    explicit QmlHandler(QObject *parent = 0);

    Q_INVOKABLE void getRoute(QString originStation, QString destStation, QDate tripDate);

    void setRouteModel(const QList<QObject*> &newRtModel)
    {
        m_routeModel = newRtModel;
        emit routeModelChanged();
    }

    QList<QObject*> routeModel() const
    {
        return m_routeModel;
    }
signals:
    void routeModelChanged();
public slots:
    void onGetRouteFinished(QNetworkReply* netReply);
private:
    QList<QObject*> m_routeModel;
};

#endif // QMLHANDLER_H
