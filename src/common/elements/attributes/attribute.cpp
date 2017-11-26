#include <iostream>
#include <string.h>

#include "attribute.h"
#include "plugins/common/simhubdeviceplugin.h"

//! marshals C++ Attribute instance to C generic struct
GenericTLV *AttributeToCGeneric(std::shared_ptr<Attribute> value)
{
    GenericTLV *retVal = make_generic(value->name().c_str(), (const char *)"-");

    // strncpy(retVal->description, value->description().c_str(), value->description().size());
    // strncpy(retVal->units, value->units().c_str(), value->units().size());

    switch (value->type()) {
    case BOOL_ATTRIBUTE:
        retVal->type = CONFIG_BOOL;
        retVal->value.bool_value = value->value<bool>();
        break;

    case FLOAT_ATTRIBUTE:
        retVal->type = CONFIG_FLOAT;
        retVal->value.float_value = value->value<float>();
        break;

    case INT_ATTRIBUTE:
        retVal->type = CONFIG_INT;
        retVal->value.int_value = value->value<int>();
        break;

    case UINT_ATTRIBUTE:
        retVal->type = CONFIG_INT;
        retVal->value.int_value = value->value<int>();
        break;

    case STRING_ATTRIBUTE:
        free(retVal);
        retVal = make_string_generic(value->name().c_str(), (const char *)"-", value->value<std::string>().c_str());
        break;

    default:
        assert(false);
        break;
    }

    retVal->ownerPlugin = value->ownerPlugin();

    return retVal;
}

//! marshals the C generic struct instance into an Attribute C++ generic container
std::shared_ptr<Attribute> AttributeFromCGeneric(GenericTLV *generic)
{
    assert(generic->ownerPlugin);
    std::shared_ptr<Attribute> retVal(new Attribute(generic->ownerPlugin));

    switch (generic->type) {
    case CONFIG_BOOL:
        retVal->setValue<bool>(generic->value.bool_value);
        retVal->setType(BOOL_ATTRIBUTE);
        break;
    case CONFIG_FLOAT:
        retVal->setValue<float>(generic->value.float_value);
        retVal->setType(FLOAT_ATTRIBUTE);
        break;
    case CONFIG_INT:
        retVal->setValue<int>(generic->value.int_value);
        retVal->setType(INT_ATTRIBUTE);
        break;
    case CONFIG_UINT:
        retVal->setValue<int>(generic->value.int_value);
        retVal->setType(INT_ATTRIBUTE);
        break;
    case CONFIG_STRING:
        retVal->setValue<std::string>(generic->value.string_value);
        retVal->setType(STRING_ATTRIBUTE);
        break;
    default:
        assert(false);
        break;
    }

    retVal->setName(generic->name);
    // retVal->setDescription(generic->description);
    // retVal->setUnits(generic->units);

    return retVal;
}

// -- instance methods

Attribute::Attribute(SPHANDLE ownerPlugin)
    : _ownerPlugin(ownerPlugin)
{
}

std::string Attribute::timestampString()
{
    using namespace std::chrono;
    using sys_milliseconds = time_point<system_clock, milliseconds>;
    return date::format("%FT%TZ", sys_milliseconds{ timestamp() });
}
