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

// template <typename T> Attribute::getValue(void)
// {
//     try {
//         return std::get<T>(_value);
//     }
//     catch(std::bad_variant_access &v) {
//         logger.log(LOG_ERROR, "invalid variant type coersion");
//     }
// }
