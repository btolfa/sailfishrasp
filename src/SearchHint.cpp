#include "SearchHint.h"

SearchHint::SearchHint(QObject *parent) : QObject(parent)
{

}


SearchHint::SearchHint(QString title, int id, QObject *parent)
    : QObject(parent)
    , _title(title)
    , _id(id)
{
}
