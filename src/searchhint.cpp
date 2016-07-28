#include "searchhint.h"

SearchHint::SearchHint(QObject *parent) : QObject(parent)
{

}


SearchHint::SearchHint(QString title, int id) {
    _title = title;
    _id = id;
}

