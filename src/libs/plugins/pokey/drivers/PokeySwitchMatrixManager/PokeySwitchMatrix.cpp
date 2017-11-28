#include "PokeySwitchMatrix.h"

PokeySwitchMatrix::PokeySwitchMatrix(sPoKeysDevice *pokey, int id, std::string name, std::string type, bool enabled)
{
    _name = name;
    _type = type;
    _id = id;
    _enabled = enabled;
    _pokey = pokey;

    // _pokey->matrixKB.matrixKBconfiguration = 1;
    // _pokey->matrixKB.matrixKBwidth = 8;
    // _pokey->matrixKB.matrixKBheight = 8;

    // int squareKBMatrixDim = 8;
    // _pokey->info.iMatrixKeyboard = 1;

    // for (int i = 0; i < squareKBMatrixDim; i++) {
    //     _pokey->matrixKB.matrixKBrowsPins[i] = i;
    //     _pokey->matrixKB.matrixKBcolumnsPins[i + squareKBMatrixDim] = i + squareKBMatrixDim;
    // }

    // memset(_pokey->matrixKB.keyMappingKeyCode, 0, squareKBMatrixDim * squareKBMatrixDim);
    // memset(_pokey->matrixKB.keyMappingKeyModifier, 0, squareKBMatrixDim * squareKBMatrixDim);
    // memset(_pokey->matrixKB.keyMappingTriggeredKey, 0, squareKBMatrixDim * squareKBMatrixDim);
    // memset(_pokey->matrixKB.keyMappingKeyCodeUp, 0, squareKBMatrixDim * squareKBMatrixDim);
    // memset(_pokey->matrixKB.keyMappingKeyModifierUp, 0, squareKBMatrixDim * squareKBMatrixDim);
    // memset(_pokey->matrixKB.matrixKBvalues, 0, squareKBMatrixDim * squareKBMatrixDim);
    
    // int32_t result = PK_MatrixKBConfigurationSet(_pokey);

    // if (result != PK_OK) {
    //     printf("---> ERR setting keyboard %i\n", result);
    // }
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

void PokeySwitchMatrix::addVirtualPin(std::string virtualPinName, bool invert, PinMaskMap &virtualPinMask, std::map<int, std::string> &valueTransforms)
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


    int keyboardMatrixDim = 8;
    int32_t result = PK_MatrixKBStatusGet(_pokey);

    static uint8_t *PrevValues = 0;

    if (!PrevValues) {
        PrevValues = (uint8_t *)calloc(64, 1);
    }

    for (int i = 0; i < 64; i++) {
        if (PrevValues[i] != _pokey->matrixKB.matrixKBvalues[i]) {
            printf("%i, %i\n", i, _pokey->matrixKB.matrixKBvalues[i]);
            PrevValues[i] = _pokey->matrixKB.matrixKBvalues[i];
        }
    }

    // scan aggregate pins first

    for (auto &sw : _switches) {
        uint8_t value = _pokey->matrixKB.matrixKBvalues[sw->pin()];

        if (sw->invert()) {
            value = !value;
        }

        sw->setCurrentValue(value);

        if (sw->previousValue() != sw->currentValue()) {

            sw->setPreviousValue(value);
            if (consumePhysicalPinValue(_virtualPins, sw)) {
                //std::cout << "/// CONSUMED: " << sw->name() << std::endl;
            }
            else {
                GenericTLV *generic = make_generic(sw->name().c_str(), sw->name().c_str());
                generic->type = CONFIG_BOOL;
                generic->value.bool_value = value;
                //std::cout << "/// AGGREGATE PIN MEMBER ISSUE: " << sw->name() << ", " << value << std::endl;
                end = retVal.insert(end, generic);
            }
        }
    }

    // now send aggregate values

    for (auto vpin : _virtualPins) {
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
