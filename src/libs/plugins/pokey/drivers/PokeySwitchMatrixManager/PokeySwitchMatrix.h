#ifndef __POKEY_SWITCH_MATRIX_H
#define __POKEY_SWITCH_MATRIX_H

#include <PoKeysLib.h>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "PokeySwitch.h"

typedef std::map<std::string, std::shared_ptr<PokeySwitch>> SwitchMap;
typedef std::vector<std::shared_ptr<PokeySwitch>> SwitchVector;

class PokeySwitchMatrix
{
protected:
    std::string _name;
    std::string _type;
    int _id;
    bool _enabled;
    sPoKeysDevice *_pokey;
    SwitchVector _switches;
    SwitchMap _virtualPins;

    bool consumePhysicalPinValue(SwitchMap &virtualPins, std::shared_ptr<PokeySwitch> pokeyPin);
    bool isPartialPin(SwitchMap &virtualPins, std::shared_ptr<PokeySwitch> pokeyPin);

public:
    PokeySwitchMatrix(sPoKeysDevice *pokey, int id, std::string name, std::string type, bool enabled);
    std::string name(void);
    int id(void);
    int addSwitch(int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin);
    std::vector<std::shared_ptr<GenericTLV>> readSwitches(void);
    void addVirtualPin(std::string virtualPinName, bool invert, PinMaskMap &virtualPinMask, std::map<int, std::string> &valueTransforms);
};

#endif
