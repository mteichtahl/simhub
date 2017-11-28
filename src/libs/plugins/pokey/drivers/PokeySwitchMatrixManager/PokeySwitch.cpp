#include <thread>

#include "PokeySwitch.h"
#include "plugins/common/utils.h"

PokeySwitch::PokeySwitch(sPoKeysDevice *pokey, int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin)
{
    _previousValue = -1;
    _pokey = pokey;
    _pin = pin;
    _enablePin = enablePin;
    _name = name;
    _invertEnablePin = invertEnablePin;
    _previousValue = -1;
    _currentValue = 0;
    _invert = invert;

    if (enablePin > 1) {
        pokey->Pins[enablePin - 1].PinFunction = PK_PinCap_digitalOutput | (invertEnablePin ? PK_PinCap_invertPin : 0x00);
    }

    if (pin > 1) {
        pokey->Pins[pin - 1].PinFunction = PK_PinCap_digitalInput | (invert ? PK_PinCap_invertPin : 0x00);
    }
    //int retVal = PK_PinConfigurationSet(pokey);
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
    if (!mapContains(_valueTransforms, (int)_currentValue)) {
        //std::cout << "/// NO TRANSFORM FOR: " << (int)_currentValue << std::endl;
        return "";
    }
    else {
        //std::cout << "/// TRANSFORM FOR: " << (int)_currentValue << std::endl;
        return _valueTransforms[_currentValue];
    }
}

GenericTLV *PokeySwitch::valueAsGeneric(void)
{
    GenericTLV *el = NULL;
    std::string value = transformedValue();

    if (value.size() > 0) {
        el = make_string_generic(name().c_str(), "pokey switch input", value.c_str());
    }

    return el;
}

using namespace std::chrono_literals;

std::pair<std::string, uint8_t> PokeySwitch::read(void)
{
    /*
    _previousValue = _currentValue;

    uint32_t result = PK_OK;

    std::this_thread::sleep_for(10ms);

    for (int i = 0; i < 8; i++) {
        // ALL HIGH EXCEPT DESIRED READ LOW
        _pokey->Pins[i].DigitalValueSet = (i == (_enablePin - 1)) ? 1 : 0;
        _pokey->Pins[i].preventUpdate = 0; //(i == (_enablePin - 1)) ? 0 : 1;
    }

    for (int i = 8; i < 16; i++) {
        _pokey->Pins[i].preventUpdate = 1;
    }

    result = PK_DigitalIOSetGet(_pokey);

    if (result != PK_OK) {
        printf("PK_DigitalIOSetGet(_pokey) returned err %i\n", result);
    }

    _currentValue = _pokey->Pins[_pin - 1].DigitalValueGet;

    for (int i = 0; i < 8; i++) {
        // ALL HIGH EXCEPT DESIRED READ LOW
        _pokey->Pins[i].DigitalValueSet = 0;
        _pokey->Pins[i].preventUpdate = 0;
    }
    std::this_thread::sleep_for(10ms);
    result = PK_DigitalIOSet(_pokey);
    */    

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
        //std::cout << "/// currentValue: " << transformedValue() << std::endl;
    }
}

bool PokeySwitch::isVirtualPinMember(std::shared_ptr<PokeySwitch> pokeyPin)
{
    return mapContains(_physPinMask, pokeyPin->name());
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
