#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <assert.h>
#include <map>
#include <stdio.h>
#include <string>
#include <tuple>

#include "attributes/attribute.h"

/**
 * base class
 */

class Element
{
public:
protected:
    std::string _name; ///< name of the element
    std::string _description; ///< description of element
    std::map<std::string, Attribute> _attributes; ///< map of elements based on attribute_t

    Element(void) { assert(false); }; ///< default constructor cannot be called - will assert

public:
    Element(std::string name, std::string description = "");
    virtual ~Element(void);
    virtual std::string getName(void) { return _name; };
    virtual std::string getDescription(void) { return _description; };
    virtual int addAttribute(Attribute attribute);
    virtual Attribute getAttribute(std::string name) = 0;
    int attributeCount();
};

#endif
