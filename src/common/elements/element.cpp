#include "element.h"
#include "../log/clog.h"
#include <stdlib.h>
#include <utility>

Element::Element(std::string name, std::string description)
    : _name(name)
    , _description(description)
{
    if (_name.empty()) {
        throw std::runtime_error("Element name cannot be empty");
    }

    if (_description.empty()) {
        throw std::runtime_error("Element description cannot be empty");
    }

    if (_name.find_first_of(" ") != std::string::npos) {
        throw std::runtime_error("Element name cannot contain spaces");
    }

    logger.log(LOG_DEBUG, "Creating Element: %s (%s)", _name.c_str(), _description.c_str());
}

Element::~Element(void)
{
    _attributes.clear();
}

int Element::attributeCount()
{
    return _attributes.size();
}

int Element::addAttribute(const Attribute attribute)
{
    if (attribute.name().empty()) {
        logger.log(LOG_ERROR, "attribute name cannot be empty");
        return -1;
    }

    const auto ret = _attributes.emplace(attribute.name(), attribute);

    if (ret.second) {
        return 0;
    }
    else {
        logger.log(LOG_ERROR, "Failed to create attribute %s - Already exists", attribute.name().c_str());
        return -1;
    }
}
