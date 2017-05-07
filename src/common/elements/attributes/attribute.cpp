#include "attribute.h"

Attribute::Attribute()
{
    _defaultValue = "0";
}

const char *Attribute::toString()
{
    char *ret = NULL;
    int len = asprintf(&ret, "%s / %s / %s / %s (name/desc/default/value)", _name.c_str(), _description.c_str(),
        _defaultValue.c_str(), _value.c_str());
    return ret;
}
