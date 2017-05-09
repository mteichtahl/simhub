#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include <variant.hpp>
#include <string>

typedef enum { INT_ATTRIBUTE = 0, FLOAT_ATTRIBUTE, STRING_ATTRIBUTE, BOOL_ATTRIBUTE } eAttribute_t;
class Attribute
{
protected:
    //std::variant<int64_t, float, double, bool, std::string> _value;

public:
    Attribute(void);

   // template <typename T> virtual T getValue(void);

    std::string _name;
    std::string _description;
    eAttribute_t _type;
    std::string _defaultValue;
    std::string _value;
    const char *toString();
    std::string getValue() { return _value; };
};

#endif
