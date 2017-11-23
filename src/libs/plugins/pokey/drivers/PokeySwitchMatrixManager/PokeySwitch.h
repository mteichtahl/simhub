
#ifndef __POKEY_SWITCH__H
#define __POKEY_SWITCH__H

#include "PoKeysLib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

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

public:
    PokeySwitch(sPoKeysDevice *pokey, int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin);
    virtual ~PokeySwitch();
    uint8_t previousValue();
    uint8_t currentValue();
    std::pair<std::string, uint8_t> read();
};

#endif