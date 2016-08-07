#ifndef SEARCHHINT_H
#define SEARCHHINT_H

#include <QObject>
#include "ValuePair.h"

class SearchHint : public QObject
{
     Q_OBJECT
     Q_PROPERTY(QString title READ title)
     Q_PROPERTY(int code READ code)

 public:
     explicit SearchHint(QObject *parent = 0);
     SearchHint(const QString& title, const int code, QObject *parent = 0);
     SearchHint(const ValuePair& value, QObject* parent = 0);
 public slots:
     QString title() { return value.string; }
     int code() { return value.code; }

 private:
     ValuePair value;
};

#endif // SEARCHHINT_H
