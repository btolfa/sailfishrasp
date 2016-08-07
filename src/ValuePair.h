#ifndef VALUEPAIR_H
#define VALUEPAIR_H

#include <QString>

struct ValuePair
{
public:
    ValuePair(const QString& string, const int code);
    ValuePair(const ValuePair& other);
    ValuePair& operator=(const ValuePair& other);
private:
    QString string;
    int code;
};

#endif // VALUEPAIR_H
