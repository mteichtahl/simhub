#ifndef __POKEY_SWITCH_MATRIX_MANAGER_H
#define __POKEY_SWITCH_MATRIX_MANAGER_H

#include "PoKeysLib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

class PokeySwitch
{
protected:
    std::string _name;
    std::string _type;
    int _id;
    bool _enabled;
    sPoKeysDevice *_pokey;

public:
    PokeySwitch(sPoKeysDevice *pokey, int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin) {
        _pokey = pokey;

        pokey->Pins[enablePin-1].PinFunction = PK_PinCap_digitalOutput | (invertEnablePin ? PK_PinCap_invertPin : 0x00);
        pokey->Pins[pin-1].PinFunction = PK_PinCap_digitalInput | (invert ? PK_PinCap_invertPin : 0x00);

        int retVal = PK_PinConfigurationSet(pokey);

        printf("-----> ret: %i\n",retVal);
    }
};

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
    PokeySwitchMatrix(sPoKeysDevice *pokey, int id, std::string name, std::string type, bool enabled)
    {
        _name = name;
        _type = type;
        _id = id;
        _enabled = enabled;
        _pokey = pokey;
    }

    std::string name() { return _name; }
    int id() { return _id; }

    int addSwitch(int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin)
    {
        _switches.push_back(std::make_shared<PokeySwitch>(_pokey, id, name, pin, enablePin, invert, invertEnablePin));
        return 0;
    }
};

class PokeySwitchMatrixManager
{
protected:
    std::vector<std::shared_ptr<PokeySwitchMatrix>> _switchMatrix;
    sPoKeysDevice *_pokey;

public:
    PokeySwitchMatrixManager(sPoKeysDevice *pokey);
    virtual ~PokeySwitchMatrixManager(void);

    int addMatrix(int id, std::string name, std::string type, bool enabled);
    std::shared_ptr<PokeySwitchMatrix> matrix(std::string name);
    std::shared_ptr<PokeySwitchMatrix> matrix(int id);
};

#endif