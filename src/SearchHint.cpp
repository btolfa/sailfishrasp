#include "SearchHint.h"

SearchHint::SearchHint(QObject *parent) : QObject(parent)
{

}


SearchHint::SearchHint(const QString& title, const int code, QObject *parent)
    : QObject(parent)
    , value(title, code)
{
}

SearchHint::SearchHint(const ValuePair &value, QObject *parent)
    : QObject(parent)
    , value(value)
{

}
