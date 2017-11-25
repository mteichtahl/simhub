
#ifndef __POKEY_SWITCH__H
#define __POKEY_SWITCH__H

#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <PoKeysLib.h>

#include "common/simhubdeviceplugin.h"

typedef std::map<std::string, std::shared_ptr<std::pair<size_t, int>>> PinMaskMap;

class PokeySwitch
{
protected:
    std::string _name;
    int _id;
    int _enablePin;
    bool _enabled;
    int _pin;
    sPoKeysDevice *_pokey;
    uint8_t _previousValue;
    uint8_t _currentValue;
    PinMaskMap _physPinMask;
    std::map<int, std::string> _valueTransforms;

    std::string transformedValue(void);

public:
    PokeySwitch(sPoKeysDevice *pokey, 
                int id, 
                std::string name, 
                int pin, 
                int enablePin, 
                bool invert, 
                bool invertEnablePin);

    virtual ~PokeySwitch(void);
    uint8_t previousValue(void);
    uint8_t currentValue(void);
    std::string name(void) { return _name; };
    std::pair<std::string, uint8_t> read(void);
    int pin(void) { return _pin; };

    void setVirtualPinMask(PinMaskMap &mask) { _physPinMask = mask; };
    void addVirtualPin(std::string name, size_t position);
    bool updateVirtualPinMask(std::shared_ptr<PokeySwitch> pokeyPin);
    void updateVirtualValue(void);
    std::shared_ptr<GenericTLV> valueAsGeneric(void);
    void setValueTransforms(std::map<int, std::string> &valueTransforms) { _valueTransforms = valueTransforms; };
};

#endif