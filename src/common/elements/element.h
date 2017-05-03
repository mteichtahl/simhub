#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <map>
#include <stdio.h>
#include <string>
#include <tuple>

#include <assert.h>

/**
 * base class
 */
class Element
{
public:
    typedef enum { INT_ATTRIBUTE = 0, FLOAT_ATTRIBUTE, STRING_ATTRIBUTE, BOOL_ATTRIBUTE } eAttributeTypes;
    typedef struct {
        std::string name;
        std::string description;
        eAttributeTypes type = eAttributeTypes::STRING_ATTRIBUTE;
        std::string defaultValue = "0";
        std::string value = "0";
    } attribute_t;

protected:
    Element(void)
    {
        assert(false);
    };

    std::string _name;
    std::string _description;
    std::map<std::string, attribute_t> _attributes;

public:
    Element(std::string name, std::string description);
    virtual ~Element(void);

    virtual std::string getName(void)
    {
        return _name;
    };

    virtual int addAttribute(const attribute_t attribute);
    virtual attribute_t getAttribute(std::string name) = 0;
};

#endif
