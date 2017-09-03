#include <string.h>

#include "elements/attributes/attribute.h"
#include "main.h"
#include "pokeyDevice.h"

using namespace std::chrono_literals;

//#define FAKE_POKEY

#if defined(FAKE_POKEY)

#define PK_EncoderValuesGet FAKE_PK_EncoderValuesGet
#define PK_DigitalIOGet FAKE_PK_DigitalIOGet
#define PK_ConnectToNetworkDevice FAKE_PK_ConnectToNetworkDevice
#define PK_DisconnectDevice FAKE_PK_DisconnectDevice
#define PK_CheckPinCapability FAKE_PK_CheckPinCapability

int FAKE_PK_EncoderValuesGet(sPoKeysDevice *pokey)
{
    return PK_ERR_GENERIC;
}

int FAKE_PK_DigitalIOGet(sPoKeysDevice *pokey)
{
    static int CallCounter = 0;

    if ((CallCounter % 5) == 0) {
        // pokey->Pins[25] = !pokey->Pins[25];
        pokey->Pins[26].DigitalValueGet = !pokey->Pins[26].DigitalValueGet;
    }

    CallCounter++;
    return PK_OK;
}

sPoKeysDevice *FAKE_PK_ConnectToNetworkDevice(sPoKeysNetworkDeviceSummary *deviceSummary)
{
    sPoKeysDevice *retVal = (sPoKeysDevice *)calloc(1, sizeof(sPoKeysDevice));
    retVal->Pins = (sPoKeysPinData *)calloc(55, sizeof(sPoKeysPinData));
    retVal->info.iPinCount = 55;

    return retVal;
}

void FAKE_PK_DisconnectDevice(sPoKeysDevice *device)
{
    assert(device);
    free(device);
}

int32_t FAKE_PK_CheckPinCapability(sPoKeysDevice *device, unsigned int pin, ePK_AllPinCap cap)
{
    return true;
}

#endif

PokeyDevice::PokeyDevice(PokeyDevicePluginStateManager *owner, sPoKeysNetworkDeviceSummary deviceSummary, uint8_t index)
{
    _callbackArg = NULL;
    _enqueueCallback = NULL;
    _owner = owner;

    _pokey = PK_ConnectToNetworkDevice(&deviceSummary);

    if (!_pokey) {
        throw std::exception();
    }

    _index = index;
    _userId = deviceSummary.UserID;
    _serialNumber = std::to_string(deviceSummary.SerialNumber);
    _firwareVersionMajorMajor = (deviceSummary.FirmwareVersionMajor >> 4) + 1;
    _firwareVersionMajor = deviceSummary.FirmwareVersionMajor & 0x0F;
    _firwareVersionMinor = deviceSummary.FirmwareVersionMinor;
    memcpy(&_ipAddress, &deviceSummary.IPaddress, 4);
    _hardwareType = deviceSummary.HWtype;
    _dhcp = deviceSummary.DHCP;

    _intToDisplayRow[0] = 0b11111100;
    _intToDisplayRow[1] = 0b01100000;
    _intToDisplayRow[2] = 0b11011010;
    _intToDisplayRow[3] = 0b11110010;
    _intToDisplayRow[4] = 0b01100110;
    _intToDisplayRow[5] = 0b10110110;
    _intToDisplayRow[6] = 0b10111110;
    _intToDisplayRow[7] = 0b11100000;
    _intToDisplayRow[8] = 0b11111110;
    _intToDisplayRow[9] = 0b11100110;

    loadPinConfiguration();
    _pollTimer.data = this;
    _pollLoop = uv_loop_new();
    uv_timer_init(_pollLoop, &_pollTimer);

    int ret = uv_timer_start(&_pollTimer, (uv_timer_cb)&PokeyDevice::DigitalIOTimerCallback, DEVICE_START_DELAY, DEVICE_READ_INTERVAL);

    if (ret == 0) {
        _pollThread = std::make_shared<std::thread>([=] { uv_run(_pollLoop, UV_RUN_DEFAULT); });
    }
}

bool PokeyDevice::ownsPin(std::string pinName)
{
    for (int i = 0; i < _pokey->info.iPinCount; i++) {
        if (_pins[i].pinName == pinName) {
            return true;
        }
    }

    return false;
}

void PokeyDevice::setCallbackInfo(EnqueueEventHandler enqueueCallback, void *callbackArg, SPHANDLE pluginInstance)
{
    _enqueueCallback = enqueueCallback;
    _callbackArg = callbackArg;
    _pluginInstance = pluginInstance;
}

void PokeyDevice::DigitalIOTimerCallback(uv_timer_t *timer, int status)
{
    PokeyDevice *self = static_cast<PokeyDevice *>(timer->data);

    assert(self);

    if (!self->_owner->successfulPreflightCompleted()) {
        return;
    }

    int encoderRetValue = PK_EncoderValuesGet(self->_pokey);

    if (encoderRetValue == PK_OK) {
        GenericTLV el;

        for (int i = 0; i < self->_encoderMap.size(); i++) {

            uint32_t step = self->_encoders[i].step;
            uint32_t newEncoderValue = self->_pokey->Encoders[i].encoderValue;
            uint32_t previousEncoderValue = self->_encoders[i].previousEncoderValue;

            uint32_t currentValue = self->_encoders[i].value;
            uint32_t min = self->_encoders[i].min;
            uint32_t max = self->_encoders[i].max;

            if (previousEncoderValue != newEncoderValue) {

                if (newEncoderValue < previousEncoderValue) {
                    // values are decreasing
                    if (currentValue <= min) {
                        self->_encoders[i].previousValue = min;
                        self->_encoders[i].value = min;
                    }
                    else {
                        self->_encoders[i].value = currentValue - step;
                    }
                }
                else {
                    // values are increasing
                    if (currentValue >= max) {
                        self->_encoders[i].previousValue = max;
                        self->_encoders[i].value = max;
                    }
                    else {
                        self->_encoders[i].value = currentValue + step;
                    }
                }

                el.ownerPlugin = self->_owner;
                el.type = CONFIG_INT;
                el.value.int_value = (int)self->_encoders[i].value;
                el.length = sizeof(uint32_t);
                el.name = (char *)self->_encoders[i].name.c_str();
                el.description = (char *)self->_encoders[i].description.c_str();
                el.units = (char *)self->_encoders[i].units.c_str();

                // enqueue the element
                self->_enqueueCallback(self, (void *)&el, self->_callbackArg);
                // set previous to equal new
                self->_encoders[i].previousEncoderValue = newEncoderValue;
            }
        }
    }

    int ret = PK_DigitalIOGet(self->_pokey);

    if (ret == PK_OK) {
        self->_owner->pinRemappingMutex().lock();

        for (int i = 0; i < self->_pokey->info.iPinCount; i++) {
            if (self->_pins[i].type == "DIGITAL_INPUT") {
                int sourcePinNumber = self->_pins[i].pinNumber;

                if (self->_pins[i].value != self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet && !self->_pins[i].skipNext) {
                    GenericTLV el;

                    // data has changed so send it off for processing
                    printf("DIN pin-index %i - %i\n", sourcePinNumber - 1, self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet);

                    el.ownerPlugin = self->_owner;
                    el.type = CONFIG_BOOL;
                    bool hackSkip = false;
                    el.length = sizeof(uint8_t);

                    if (self->_owner->pinRemapped(self->_pins[i].pinName)) {
                        // KLUDGE: as each device has its own polling thread, the logic
                        // below is a critical
                        //         section because it can touch the state of multiple device
                        //         pins

                        std::pair<std::shared_ptr<PokeyDevice>, std::string> remappedPinInfo = self->_owner->remappedPinDetails(self->_pins[i].pinName);
                        int remappedPinIndex = remappedPinInfo.first->pinIndexFromName(remappedPinInfo.second);

                        // remappedPinInfo.first->pins()[remappedPinIndex].previousValue =
                        // self->_pins[self->_pins[i].pinNumber - 1].value;
                        self->_pins[i].previousValue = self->_pins[self->_pins[i].pinNumber - 1].value;

                        remappedPinInfo.first->_pins[remappedPinIndex].previousValue = self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet; // self->_pins[i].previousValue;
                        // remappedPinInfo.first->_pins[remappedPinIndex].previousValue =
                        // self->_pins[i].previousValue;

                        remappedPinInfo.first->_pins[remappedPinIndex].value = self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet;
                        self->_pins[i].value = self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet;

                        el.name = (char *)remappedPinInfo.second.c_str();
                        el.value.bool_value = self->_pokey->Pins[sourcePinNumber - 1].DigitalValueGet;

                        if (el.value.bool_value == 0) {
                            remappedPinInfo.first->_pins[remappedPinIndex].skipNext = true;
                        }
                        else {
                            if (!remappedPinInfo.first->_pins[remappedPinIndex].skipNext) {
                                self->_owner->pinRemappingMutex().unlock();
                            }

                            remappedPinInfo.first->_pins[remappedPinIndex].skipNext = false;
                            printf("---> sleeping for other poll thread\n");

                            // give any other remapped polling threads a chance to send a
                            // state change
                            std::this_thread::sleep_for(150ms);
                            if (remappedPinInfo.first->_pins[remappedPinIndex].skipNext) {
                                printf("---> other poll thread changed skip value\n");
                                hackSkip = true;
                            }
                        }

                        printf("--> remapping %s to  %s\n", self->_pins[i].pinName.c_str(), remappedPinInfo.first->pins()[remappedPinIndex].pinName.c_str());
                    }
                    else {
                        el.name = (char *)self->_pins[i].pinName.c_str();
                        self->_pins[i].previousValue = self->_pins[i].value;
                        self->_pins[i].value = self->_pokey->Pins[self->_pins[i].pinNumber - 1].DigitalValueGet;
                        el.value.bool_value = self->_pins[i].value;
                    }

                    if (hackSkip) {
                        printf("HACKSKIP, %s, %i\n", self->_pins[i].pinName.c_str(), self->_pins[i].value);
                        self->_owner->pinRemappingMutex().unlock();
                        return;
                    }

                    el.description = (char *)self->_pins[i].description.c_str();
                    el.units = (char *)self->_pins[i].units.c_str();

                    std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(&el);
                    TransformFunction transformer = self->_owner->transformForPinName(self->_pins[i].pinName);

                    if (transformer) {
                        std::string transformedValue = transformer(attribute->valueToString(), "NULL", "NULL");

                        attribute->setType(STRING_ATTRIBUTE);
                        attribute->setValue(transformedValue);
                        GenericTLV *transformedGeneric = AttributeToCGeneric(attribute);

                        if (el.value.bool_value == 0 || !self->_owner->coalescedDeliveryValue().second) {
                            self->_owner->coalescedDeliveryValue().first = el.name;

                            if (self->_owner->coalescedDeliveryValue().second) {
                                free(self->_owner->coalescedDeliveryValue().second);
                            }
                            self->_owner->coalescedDeliveryValue().second = transformedGeneric;
                            self->_owner->pendingCoalescedDelivery() = true;
                        }
                    }
                    else {
                        printf("---> %s\n", (char *)self->_pins[i].pinName.c_str());
                        self->_enqueueCallback(self, (void *)&el, self->_callbackArg);
                    }
                }
            }
        }
        self->_owner->pinRemappingMutex().unlock();
    }
    else {
        printf("TRANSFER ERROR\n");
    }

    // KLUDGE KLUDGE KLUDGE
    if (self->_owner->pendingCoalescedDelivery()) {
        self->_owner->pendingCoalescedDelivery() = false;
        std::this_thread::sleep_for(150ms);
        self->_owner->pinRemappingMutex().lock();
        if (self->_owner->coalescedDeliveryValue().second) {
            printf("coalescing on: %s", self->_owner->coalescedDeliveryValue().first.c_str());
            self->_enqueueCallback(self, (void *)self->_owner->coalescedDeliveryValue().second, self->_callbackArg);
            free(self->_owner->coalescedDeliveryValue().second);
            self->_owner->coalescedDeliveryValue().second = NULL;
        }
        self->_owner->pinRemappingMutex().unlock();
    }
}

void PokeyDevice::addPin(int pinIndex, std::string pinName, int pinNumber, std::string pinType, int defaultValue, std::string description, bool invert)
{
    if (pinType == "DIGITAL_OUTPUT")
        outputPin(pinNumber);
    if (pinType == "DIGITAL_INPUT")
        inputPin(pinNumber, invert);

    mapNameToPin(pinName.c_str(), pinNumber);

    _pins[pinIndex].pinName = pinName;
    _pins[pinIndex].pinIndex = pinIndex;
    _pins[pinIndex].type = pinType.c_str();
    _pins[pinIndex].pinNumber = pinNumber;
    _pins[pinIndex].defaultValue = defaultValue;
    _pins[pinIndex].value = defaultValue;
    _pins[pinIndex].description = description;
}

void PokeyDevice::startPolling()
{
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

void PokeyDevice::stopPolling()
{
    assert(_pollLoop);
    uv_stop(_pollLoop);

    if (_pollThread->joinable())
        _pollThread->join();
}

/**
 *   @brief  Default  destructor for PokeyDevice
 *
 *   @return nothing
 */
PokeyDevice::~PokeyDevice()
{
    stopPolling();

    if (_pollThread) {
        if (_pollThread->joinable()) {
            _pollThread->join();
        }
    }

    PK_DisconnectDevice(_pokey);
}

std::string PokeyDevice::name()
{
#if defined(FAKE_POKEY)
    return "test" + _serialNumber;
#endif

    std::string tmp((char *)deviceData().DeviceName);
    return tmp;
}

std::string PokeyDevice::hardwareTypeString()
{
    if (_hardwareType == 31) {
        return "Pokey 57E";
    }
    return "Unknown";
}

bool PokeyDevice::validatePinCapability(int pin, std::string type)
{
    assert(_pokey);
    bool retVal = false;

    if (type == "DIGITAL_OUTPUT") {
        retVal = isPinDigitalOutput(pin - 1);
    }
    else if (type == "DIGITAL_INPUT") {
        retVal = isPinDigitalInput(pin - 1);
    }
    return retVal;
}

bool PokeyDevice::validateEncoder(int encoderNumber)
{
    assert(_pokey);
    bool retVal = false;

    if (encoderNumber == ENCODER_1) {
        //! TODO: Check pins 1 and 2 are not allocated already
        retVal = isEncoderCapable(1) && isEncoderCapable(2);
    }
    else if (encoderNumber == ENCODER_2) {
        //! TODO: Check pins 5 and 6 are not allocated already
        retVal = isEncoderCapable(5) && isEncoderCapable(6);
    }
    else if (encoderNumber == ENCODER_3) {
        //! TODO: Check pins 15 and 16 are not allocated already
        retVal = isEncoderCapable(15) && isEncoderCapable(16);
    }

    return retVal;
}

bool PokeyDevice::isEncoderCapable(int pin)
{

    switch (pin) {
    case 1:
        return (bool)PK_CheckPinCapability(_pokey, 0, PK_AllPinCap_fastEncoder1A);
    case 2:
        return (bool)PK_CheckPinCapability(_pokey, 1, PK_AllPinCap_fastEncoder1B);
    case 5:
        return (bool)PK_CheckPinCapability(_pokey, 4, PK_AllPinCap_fastEncoder2A);
    case 6:
        return (bool)PK_CheckPinCapability(_pokey, 5, PK_AllPinCap_fastEncoder2B);
    case 15:
        return (bool)PK_CheckPinCapability(_pokey, 14, PK_AllPinCap_fastEncoder3A);
    case 16:
        return (bool)PK_CheckPinCapability(_pokey, 14, PK_AllPinCap_fastEncoder3B);
    default:
        return false;
    }

    return false;
}

void PokeyDevice::addEncoder(
    int encoderNumber, uint32_t defaultValue, std::string name, std::string description, int min, int max, int step, int invertDirection, std::string units)
{
    assert(encoderNumber >= 1);

    PK_EncoderConfigurationGet(_pokey);
    int encoderIndex = encoderNumber - 1;

    _pokey->Encoders[encoderIndex].encoderValue = defaultValue;
    _pokey->Encoders[encoderIndex].encoderOptions = 0b11;

    if (encoderNumber == 1) {
        if (invertDirection) {
            _pokey->Encoders[encoderIndex].channelApin = 1;
            _pokey->Encoders[encoderIndex].channelBpin = 0;
        }
        else {
            _pokey->Encoders[encoderIndex].channelApin = 1;
            _pokey->Encoders[encoderIndex].channelBpin = 0;
        }
    }
    else if (encoderNumber == 2) {
        if (invertDirection) {
            _pokey->Encoders[encoderIndex].channelApin = 5;
            _pokey->Encoders[encoderIndex].channelBpin = 4;
        }
        else {
            _pokey->Encoders[encoderIndex].channelApin = 4;
            _pokey->Encoders[encoderIndex].channelBpin = 5;
        }
    }
    else if (encoderNumber == 3) {
        if (invertDirection) {
            _pokey->Encoders[encoderIndex].channelApin = 15;
            _pokey->Encoders[encoderIndex].channelBpin = 14;
        }
        else {
            _pokey->Encoders[encoderIndex].channelApin = 14;
            _pokey->Encoders[encoderIndex].channelBpin = 15;
        }
    }

    _encoders[encoderIndex].name = name;
    _encoders[encoderIndex].number = encoderNumber;
    _encoders[encoderIndex].defaultValue = defaultValue;
    _encoders[encoderIndex].value = defaultValue;
    _encoders[encoderIndex].previousValue = defaultValue;
    _encoders[encoderIndex].previousEncoderValue = defaultValue;
    _encoders[encoderIndex].min = min;
    _encoders[encoderIndex].max = max;
    _encoders[encoderIndex].step = step;
    _encoders[encoderIndex].units = units;
    _encoders[encoderIndex].description = description;

    int val = PK_EncoderConfigurationSet(_pokey);

    if (val == PK_OK) {
        PK_EncoderValuesSet(_pokey);
        mapNameToEncoder(name.c_str(), encoderNumber);
    }
    else {
        // throw exception
    }
}

void PokeyDevice::addMatrixLED(int id, std::string name, std::string type)
{
    PK_MatrixLEDConfigurationGet(_pokey);
    _matrixLED[id].name = name;
    _matrixLED[id].type = type;

    mapNameToMatrixLED(name, id);
}

void PokeyDevice::addGroupToMatrixLED(int id, int displayId, std::string name, int digits, int position)
{
    _matrixLED[displayId].group[position].name = name;
    _matrixLED[displayId].group[position].position = position;
    _matrixLED[displayId].group[position].length = digits;
    _matrixLED[displayId].group[position].value = 0;
}

void PokeyDevice::configMatrixLED(int id, int rows, int cols, int enabled)
{
    _pokey->MatrixLED[id].rows = rows;
    _pokey->MatrixLED[id].columns = cols;
    _pokey->MatrixLED[id].displayEnabled = enabled;
    _pokey->MatrixLED[id].RefreshFlag = 1;
    _pokey->MatrixLED[id].data[0] = 0;
    _pokey->MatrixLED[id].data[1] = 0;
    _pokey->MatrixLED[id].data[2] = 0;
    _pokey->MatrixLED[id].data[3] = 0;
    _pokey->MatrixLED[id].data[4] = 0;
    _pokey->MatrixLED[id].data[5] = 0;
    _pokey->MatrixLED[id].data[6] = 0;
    _pokey->MatrixLED[id].data[7] = 0;

    int32_t ret = PK_MatrixLEDConfigurationSet(_pokey);
    PK_MatrixLEDUpdate(_pokey);
}

uint32_t PokeyDevice::targetValue(std::string targetName, int value)
{
    uint8_t displayNum = displayFromName(targetName);
    displayNumber(displayNum, targetName, value);
    return 0;
}

uint32_t PokeyDevice::targetValue(std::string targetName, bool value)
{
    uint32_t retValue = -1;
    uint8_t pin = pinFromName(targetName) - 1;

    if (pin >= 0) {
        retValue = PK_DigitalIOSetSingle(_pokey, pin, value);
    }

    if (retValue == PK_ERR_TRANSFER) {
        printf("----> PK_ERR_TRANSFER pin %d --> %d %d\n\n", pin, (uint8_t)value, retValue);
    }
    else if (retValue == PK_ERR_GENERIC) {
        printf("----> PK_ERR_GENERIC pin %d --> %d %d\n\n", pin, (uint8_t)value, retValue);
    }
    else if (retValue == PK_ERR_PARAMETER) {
        printf("----> PK_ERR_PARAMETER pin %d --> %d %d\n\n", pin, (uint8_t)value, retValue);
    }

    return retValue;
}

uint8_t PokeyDevice::displayNumber(uint8_t displayNumber, std::string targetName, int value)
{
    int groupIndex = 0;

    for (int i = 0; i < MAX_MATRIX_LED_GROUPS; i++) {
        if (_matrixLED[displayNumber].group[i].name == targetName) {
            groupIndex = i;
        }
    }

    // we should only display +ve values
    if (value < -1) {
        value = value * -1;
    }

    std::string charString = std::to_string(value);
    int numberOfChars = charString.length();
    int groupLength = _matrixLED[displayNumber].group[groupIndex].length;

    if (value == 0) {
        int position = _matrixLED[displayNumber].group[groupIndex].position;
        for (int i = position; i < (groupLength + position); i++) {
            _pokey->MatrixLED[displayNumber].data[i] = 0b00000000;
        }
        _pokey->MatrixLED[displayNumber].data[(position + groupLength) - 1] = _intToDisplayRow[0];
    }

    if (numberOfChars <= groupLength) {

        for (int i = 0; i < numberOfChars; i++) {
            int displayOffset = (int)charString.at(i) - 48;
            int convertedValue = _intToDisplayRow[displayOffset];
            int position = groupIndex + i;

            if (value > 0) {
                _matrixLED[displayNumber].group[groupIndex].value = convertedValue;
                _pokey->MatrixLED[displayNumber].data[position] = convertedValue;
            }
            else if (value == -1) {
                for (int i = groupIndex; i < groupLength + groupIndex; i++) {
                    _pokey->MatrixLED[displayNumber].data[i] = 0b00000000;
                }
            }
        }
    }

    _pokey->MatrixLED[displayNumber].RefreshFlag = 1;

    if (PK_MatrixLEDUpdate(_pokey) != PK_OK) {
        printf("---> could not update Maxtix LED \n");
        return -1;
    }

    return 0;
}

uint32_t PokeyDevice::outputPin(uint8_t pin)
{
    _pokey->Pins[--pin].PinFunction = PK_PinCap_digitalOutput | PK_PinCap_invertPin;
    return PK_PinConfigurationSet(_pokey);
}

uint32_t PokeyDevice::inputPin(uint8_t pin, bool invert)
{
    int pinSetting = PK_PinCap_digitalInput;

    if (invert) {
        pinSetting = pinSetting | PK_PinCap_invertPin;
    }

    _pokey->Pins[--pin].PinFunction = pinSetting;
    return PK_PinConfigurationSet(_pokey);
}

int32_t PokeyDevice::name(std::string name)
{
    strncpy((char *)_pokey->DeviceData.DeviceName, name.c_str(), 30);
    return PK_DeviceNameSet(_pokey);
}

uint8_t PokeyDevice::displayFromName(std::string targetName)
{
    std::map<std::string, int>::iterator it;
    it = _displayMap.find(targetName);

    if (it != _displayMap.end()) {
        return it->second;
    }
    else {
        printf("---> cant find display\n");
        return -1;
    }
}

int PokeyDevice::pinIndexFromName(std::string targetName)
{
    for (size_t i = 0; i < MAX_PINS; i++) {
        if (_pins[i].pinName == targetName) {
            return _pins[i].pinIndex;
        }
    }

    return -1;
}

int PokeyDevice::pinFromName(std::string targetName)
{
    std::map<std::string, int>::iterator it;
    it = _pinMap.find(targetName);

    if (it != _pinMap.end()) {
        return it->second;
    }
    else
        return -1;
}

void PokeyDevice::mapNameToPin(std::string name, int pin)
{
    _pinMap.emplace(name, pin);
}

void PokeyDevice::mapNameToEncoder(std::string name, int encoderNumber)
{
    _encoderMap.emplace(name, encoderNumber);
}

void PokeyDevice::mapNameToMatrixLED(std::string name, int id)
{
    _displayMap.emplace(name, id);
}

bool PokeyDevice::isPinDigitalOutput(uint8_t pin)
{
    return (bool)PK_CheckPinCapability(_pokey, pin, PK_AllPinCap_digitalOutput);
}

bool PokeyDevice::isPinDigitalInput(uint8_t pin)
{
    return (bool)PK_CheckPinCapability(_pokey, pin, PK_AllPinCap_digitalInput);
}
