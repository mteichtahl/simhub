#include "element.h"

Element::Element(std::string name, std::string description) : 
    _name(name), 
    _description(description)
{

}

Element::~Element(void)
{
}

void Element::addAttribute(std::string name, 
                           std::string value, 
                           Element::eAttributeTypes type)
{

}

void Element::addAttributes(const std::map<std::string, std::string>& attributes)
{
}

