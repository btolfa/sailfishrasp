#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QJsonObject>
#include <QVariantMap>

class Thread : public QObject {
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);

    explicit Thread(const QJsonObject &jsonObject, QObject *parent = 0);

    Q_INVOKABLE QVariant get(const QString &key);

private:
    QVariantMap t_data;
};

#endif // THREAD_H
