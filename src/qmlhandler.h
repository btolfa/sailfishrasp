#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QObject>
#include <QListData>
#include <QAbstractListModel>

class QmlHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QAbstractListModel routeModel READ routeModel WRITE setRouteModel NOTIFY routeModelChanged)
public:
    explicit QmlHandler(QObject *parent = 0);

    void setRouteModel(const QAbstractListModel &newRtModel)
    {
        m_routeModel = newRtModel;
        emit routeModelChanged();
    }

    QAbstractListModel routeModel() const
    {
        return m_routeModel;
    }
signals:
    void routeModelChanged();
public slots:
private:
    QAbstractListModel m_routeModel;
};

#endif // QMLHANDLER_H
