#include <utility>
#include <assert.h>
#include <thread>

#include "PokeySwitch.h"
#include "plugins/common/utils.h"

PokeySwitch::PokeySwitch(sPoKeysDevice *pokey, int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin)
{
    _pokey = pokey;
    _pin = pin;
    _enablePin = enablePin;
    _name = name;
    _currentValue = 0;
    _previousValue = 0;

    pokey->Pins[enablePin - 1].PinFunction = PK_PinCap_digitalOutput | (invertEnablePin ? PK_PinCap_invertPin : 0x00);
    pokey->Pins[pin - 1].PinFunction = PK_PinCap_digitalInput | (invert ? PK_PinCap_invertPin : 0x00);

    int retVal = PK_PinConfigurationSet(pokey);
}

PokeySwitch::~PokeySwitch(void)
{
}

uint8_t PokeySwitch::previousValue()
{
    return _previousValue;
}

uint8_t PokeySwitch::currentValue()
{
    return _currentValue;
}

void PokeySwitch::addVirtualPin(std::string name, size_t position)
{
    _physPinMask[name] = std::make_shared<std::pair<size_t, int>>(position, 0);
}

std::string PokeySwitch::transformedValue(void)
{
    return _valueTransforms[_currentValue];
}

std::shared_ptr<GenericTLV> PokeySwitch::valueAsGeneric(void)
{
    std::shared_ptr<GenericTLV> el = std::make_shared<GenericTLV>();

    el->name = (char *)calloc(name().size() + 1, 0);
    strncpy(el->name, (char *)name().c_str(), name().size() + 1);
    el->type = CONFIG_STRING;
    std::string value = transformedValue();
    el->value.string_value = (char *)calloc(value.size() + 1, 1);
    strncpy(el->value.string_value, value.c_str(), value.size() + 1);
    return el;
}

using namespace std::chrono_literals;

std::pair<std::string, uint8_t> PokeySwitch::read(void)
{
    _previousValue = _currentValue;
    
    uint32_t result = PK_OK;

    for (int i = 0; i < 8; i++) {
        _pokey->Pins[i].DigitalValueSet = (i == (_enablePin - 1)) ? 1 : 0;
    }
    
    result = PK_DigitalIOSetGet(_pokey);
    std::this_thread::sleep_for(5ms);

    if (result != PK_OK) {
        printf("PK_DigitalIOSetGet(_pokey) returned err %i\n", result);
    }

    _currentValue = _pokey->Pins[_pin - 1].DigitalValueGet;

    return std::make_pair(_name, _currentValue);
}


void PokeySwitch::updateVirtualValue(void)
{
    _previousValue = _currentValue;

    _currentValue = 0;

    for (PinMaskMap::iterator iter = _physPinMask.begin(); iter != _physPinMask.end(); iter++) {
        int value = (*iter).second->second;
        size_t pos = (*iter).second->first;
        std::string name = (*iter).first;
        _currentValue |= (value << pos);
    }

    if (_currentValue != _previousValue) {
        std::cout << "/// currentValue: " << transformedValue() << std::endl;
    }
}

bool PokeySwitch::updateVirtualPinMask(std::shared_ptr<PokeySwitch> pokeyPin)
{
    bool retVal = false;

    if (mapContains(_physPinMask, pokeyPin->name())) {
        retVal = true;
        std::shared_ptr<std::pair<size_t, int>> valueInfo = _physPinMask[pokeyPin->name()];
        valueInfo->second = pokeyPin->currentValue();
    }

    return retVal;
}


