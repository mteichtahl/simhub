#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <map>
#include <tuple>
#include <string>

#include <assert.h>

/**
 * base class
 */

class Element
{
protected:
    Element(void) { assert(false); };

    std::string _name;
    std::string _description;

public:
    typedef enum {
        INT_ATTRIBUTE,
        FLOAT_ATTRIBUTE,
        STRING_ATTRIBUTE,
        BOOL_ATTRIBUTE
    } eAttributeTypes;

    Element(std::string name, std::string description);
    virtual ~Element(void);

    virtual std::string getName(void) { return _name; };

    virtual void addAttribute(std::string name, 
                              std::string value, 
                              Element::eAttributeTypes type);
    virtual void addAttributes(const std::map<std::string, std::string>& attributes);
    virtual std::tuple<std::string, Element::eAttributeTypes> getAttribute(std::string name) = 0;
};

#endif
