#include "source.h"

Element::attribute_t Source::getAttribute(std::string name)
{
    return _attributes.at(name);
}
