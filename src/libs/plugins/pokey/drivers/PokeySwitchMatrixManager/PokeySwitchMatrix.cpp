#include "PokeySwitchMatrix.h"

PokeySwitchMatrix::PokeySwitchMatrix(sPoKeysDevice *pokey, int id, std::string name, std::string type, bool enabled)
{
    _name = name;
    _type = type;
    _id = id;
    _enabled = enabled;
    _pokey = pokey;
}

std::string PokeySwitchMatrix::name()
{
    return _name;
}
int PokeySwitchMatrix::id()
{
    return _id;
}

int PokeySwitchMatrix::addSwitch(int id, std::string name, int pin, int enablePin, bool invert, bool invertEnablePin)
{
    _switches.push_back(std::make_shared<PokeySwitch>(_pokey, id, name, pin, enablePin, invert, invertEnablePin));
    return 0;
}

std::vector<std::pair<std::string, uint8_t>> PokeySwitchMatrix::readSwitches()
{
    std::vector<std::pair<std::string, uint8_t>> retVal;
    auto end = retVal.end();

    for (auto &sw : _switches) {
        auto swData = sw->read();

        if (sw->previousValue() != sw->currentValue()) {
            end = retVal.insert(end, swData);
        }
    }

    return retVal;
}
