#ifndef __POKEY_SWITCH_MATRIX_H
#define __POKEY_SWITCH_MATRIX_H

#include <PoKeysLib.h>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "PokeySwitch.h"

class PokeySwitchMatrix
{
protected:
    std::string _name;
    std::string _type;
    int _id;
    bool _enabled;
    sPoKeysDevice *_pokey;

    std::vector<std::shared_ptr<PokeySwitch>> _switches;

public:
    PokeySwitchMatrix(sPoKeysDevice *pokey, int id, std::string name, std::string type, bool enabled);
    std::string name();
    int id();
    int addSwitch(int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin);
    std::vector<std::pair<std::string, uint8_t>> readSwitches();
};

#endif
