#include "PokeySwitch.h"

PokeySwitch::PokeySwitch(sPoKeysDevice *pokey, int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin)
{
    _pokey = pokey;
    _pin = pin;
    _enablePin = enablePin;
    _name = name;

    pokey->Pins[enablePin - 1].PinFunction = PK_PinCap_digitalOutput | (invertEnablePin ? PK_PinCap_invertPin : 0x00);
    pokey->Pins[pin - 1].PinFunction = PK_PinCap_digitalInput | (invert ? PK_PinCap_invertPin : 0x00);

    int retVal = PK_PinConfigurationSet(pokey);
}

PokeySwitch::~PokeySwitch(void){

}

uint8_t PokeySwitch::previousValue()
{
    return _previousValue;
}
uint8_t PokeySwitch::currentValue()
{
    return _currentValue;
}

std::pair<std::string, uint8_t> PokeySwitch::read()
{
    _previousValue = _currentValue;

    PK_DigitalIOSetSingle(_pokey, _enablePin, 1);
    PK_DigitalIOGetSingle(_pokey, _pin, &_currentValue);
    PK_DigitalIOSetSingle(_pokey, _enablePin, 0);

    return std::make_pair(_name, _currentValue);
}

