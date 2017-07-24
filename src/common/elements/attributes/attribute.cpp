#include <iostream>
#include "attribute.h"

Attribute::Attribute(void)
{
    // _defaultValue = "0";
    // _value = 0;
}

Attribute::~Attribute(void)
{
}

std::string Attribute::timestampString()
{
    using namespace std::chrono;
    using sys_milliseconds = time_point<system_clock, milliseconds>;
    return date::format("%FT%TZ", sys_milliseconds{ timestamp() });
}

std::chrono::milliseconds Attribute::timestamp()
{
    return _timestamp;
}
