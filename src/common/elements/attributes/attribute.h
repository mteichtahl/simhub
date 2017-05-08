#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include <string>

typedef enum { INT_ATTRIBUTE = 0, FLOAT_ATTRIBUTE, STRING_ATTRIBUTE, BOOL_ATTRIBUTE } eAttribute_t;
class Attribute
{
protected:
public:
    Attribute();
    std::string _name;
    std::string _description;
    eAttribute_t _type;
    std::string _defaultValue;
    const char *toString();
    std::string getValue() { return _value; };
    std::string _value;
};

#endif
