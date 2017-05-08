#ifndef __SOURCE_H
#define __SOURCE_H

#include <assert.h>
#include <stdio.h>
#include <string>

#include "../../elements/element.h"
class Source : public Element
{
protected:
public:
    Source(std::string name, std::string description)
        : Element(name, description){};
    Attribute getAttribute(std::string name);
};

#endif
