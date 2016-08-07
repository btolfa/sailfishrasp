#include "ValuePair.h"

ValuePair::ValuePair(const QString& string, const int code)
    : string(string), code(code)
{
}


ValuePair::ValuePair(const ValuePair &other)
    : string(other.string), code(other.code)
{
}

ValuePair &ValuePair::operator=(const ValuePair &other)
{
    if (&other == this) {
        return *this;
    }

    string = other.string;
    code = other.code;

    return *this;
}
