#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include "../../../libs/tz/tz.h" // https://github.com/HowardHinnant/date
#include <chrono>
#include <sstream>
#include <string>
#include <variant.hpp>

typedef enum { INT_ATTRIBUTE = 0, FLOAT_ATTRIBUTE, STRING_ATTRIBUTE, BOOL_ATTRIBUTE, UINT_ATTRIBUTE } eAttribute_t;

class Attribute
{
protected:
    mpark::variant<int64_t, int, float, double, bool, std::string> _value;
    mpark::variant<int64_t, int, float, double, bool, std::string> _defaultValue;

public:
    std::string _name;
    std::string _description;
    std::chrono::milliseconds _timestamp;
    eAttribute_t _type;

    Attribute(void);
    virtual ~Attribute(void);

    template <typename T> void setValue(T value)
    {
        _value = value;
        _timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    };
    template <typename T> T getValue(void) { return mpark::get<T>(_value); };

    std::string getValueToString(void)
    {
        std::ostringstream oss; // create a stream

        switch (_type) {
        case INT_ATTRIBUTE:
            oss << mpark::get<int>(_value); // insert value to stream
            break;
        case FLOAT_ATTRIBUTE:
            oss << mpark::get<float>(_value); // insert value to stream
            break;
        case STRING_ATTRIBUTE:
            oss << mpark::get<std::string>(_value); // insert value to stream
            break;
        case UINT_ATTRIBUTE:
            oss << mpark::get<int>(_value); // insert value to stream
            break;
        case BOOL_ATTRIBUTE:
            oss << mpark::get<bool>(_value); // insert value to stream
            break;
        default:
            assert(false);
            break;
        }
        return oss.str(); // extract value and return
    }

    std::string timestampString();
    std::chrono::milliseconds timestamp();
};

#endif
