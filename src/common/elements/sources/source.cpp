#include "source.h"

Attribute Source::getAttribute(std::string name)
{
    return _attributes.at(name);
}
