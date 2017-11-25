#include <string.h>

#include "PokeySwitchMatrix.h"

PokeySwitchMatrix::PokeySwitchMatrix(sPoKeysDevice *pokey, 
                                     int id, 
                                     std::string name, 
                                     std::string type,
                                     bool enabled)
{
    _name = name;
    _type = type;
    _id = id;
    _enabled = enabled;
    _pokey = pokey;
}

std::string PokeySwitchMatrix::name(void)
{
    return _name;
}
int PokeySwitchMatrix::id(void)
{
    return _id;
}

int PokeySwitchMatrix::addSwitch(int id, 
                                 std::string name,
                                 int pin,
                                 int enablePin,
                                 bool invert, 
                                 bool invertEnablePin)
{
    _switches.push_back(std::make_shared<PokeySwitch>(_pokey, 
                                                      id,
                                                      name,
                                                      pin,
                                                      enablePin,
                                                      invert,
                                                      invertEnablePin));


    std::cout << "/// JUST ADDED SWITCH: " << name << std::endl;

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

std::vector<std::shared_ptr<GenericTLV>> PokeySwitchMatrix::readSwitches(void)
{
    std::vector<std::shared_ptr<GenericTLV>> retVal;
    auto end = retVal.end();

    for (auto &sw : _switches) {
        if (isPartialPin(_virtualPins, sw)) {
            sw->setIsPartialPin(true);
        }

        std::pair<std::string, uint8_t> swData = sw->read();

        if (sw->previousValue() != sw->currentValue()) {
            if (!consumePhysicalPinValue(_virtualPins, sw)) {        
                std::shared_ptr<GenericTLV> el = std::make_shared<GenericTLV>();
                el->type = CONFIG_BOOL;
                el->name = (char *)calloc(sw->name().size() + 1, 1);
                strncpy(el->name, (char *)sw->name().c_str(), sw->name().size() + 1);
                el->value.bool_value = (int)swData.second;
                end = retVal.insert(end, el);
                std::cout << "// GOT CHANGE FOR " << el->name << ", VALUE: " << el->value.bool_value << std::endl;
            }
            else {
                std::cout << "/// CONSUMED: " << sw->name() << std::endl;
            }
        }
    }

    for (auto vpin: _virtualPins) {
        vpin.second->updateVirtualValue();

        if (vpin.second->currentValue() != vpin.second->previousValue()) {
            end = retVal.insert(end, vpin.second->valueAsGeneric());
        }
    }

    return retVal;
}
