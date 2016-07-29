#include "thread.h"


Thread::Thread(QObject *parent) : QObject(parent) { }


Thread::Thread(const QJsonObject &jsonObject, QObject *parent) : QObject(parent) {
    this->t_data = jsonObject.toVariantMap();
}


QVariant Thread::get(const QString &key) {
    return this->t_data[key];
}
