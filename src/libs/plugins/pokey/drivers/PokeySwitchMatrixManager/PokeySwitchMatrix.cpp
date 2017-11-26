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

void PokeySwitchMatrix::addVirtualPin(std::string virtualPinName, 
                                      bool invert, 
                                      PinMaskMap &virtualPinMask,
                                      std::map<int, std::string> &valueTransforms)
{
    std::shared_ptr<PokeySwitch> pin = std::make_shared<PokeySwitch>(_pokey, 0, virtualPinName, 0, 0, invert, false);
    pin->setVirtualPinMask(virtualPinMask);
    pin->setValueTransforms(valueTransforms);
    _virtualPins[virtualPinName] = pin;
}

bool PokeySwitchMatrix::consumePhysicalPinValue(SwitchMap &virtualPins, std::shared_ptr<PokeySwitch> pokeyPin)
{
    bool retVal = false;

    // give all virtual pins a chance to use the value of this physical pin
    for (SwitchMap::iterator iter = virtualPins.begin(); iter != virtualPins.end(); iter++) {
        if ((*iter).second->updateVirtualPinMask(pokeyPin)) {
            retVal = true;
        }
    }

    return retVal;
}

bool PokeySwitchMatrix::isPartialPin(SwitchMap &virtualPins, std::shared_ptr<PokeySwitch> pokeyPin)
{
    bool retVal = false;

    // give all virtual pins a chance to use the value of this physical pin
    for (SwitchMap::iterator iter = virtualPins.begin(); iter != virtualPins.end(); iter++) {
        if ((*iter).second->isVirtualPinMember(pokeyPin)) {
            retVal = true;
        }
    }

    return retVal;
}

std::vector<GenericTLV *> PokeySwitchMatrix::readSwitches()
{
    std::vector<GenericTLV *> retVal;
    auto end = retVal.end();

    for (auto &sw : _switches) {
        if (isPartialPin(_virtualPins, sw)) {
            sw->setIsPartialPin(true);
        }

        std::pair<std::string, uint8_t> swData = sw->read();

        if (sw->previousValue() != sw->currentValue()) {
            if (!consumePhysicalPinValue(_virtualPins, sw)) {        
                GenericTLV *el = make_generic(sw->name().c_str(), "-");
                el->type = CONFIG_BOOL;
                el->value.bool_value = (int)swData.second;
                end = retVal.insert(end, el);
            }
            else {
                std::cout << "/// CONSUMED: " << sw->name() << std::endl;
            }
        }
    }

    for (auto vpin: _virtualPins) {
        vpin.second->updateVirtualValue();
        if (vpin.second->currentValue() != vpin.second->previousValue()) {
	    GenericTLV *generic = vpin.second->valueAsGeneric();
	    if (generic) {
                end = retVal.insert(end, generic);
	    }
        }
    }

    return retVal;
}

