#include "pokeyDevice.h"
#include <string.h>

PokeyDevice::PokeyDevice(sPoKeysNetworkDeviceSummary deviceSummary, uint8_t index)
{
    _pokey = PK_ConnectToNetworkDevice(&deviceSummary);
    _index = index;
    _userId = deviceSummary.UserID;
    _serialNumber = std::to_string(deviceSummary.SerialNumber);
    _firwareVersionMajorMajor = (deviceSummary.FirmwareVersionMajor >> 4) + 1;
    _firwareVersionMajor = deviceSummary.FirmwareVersionMajor & 0x0F;
    _firwareVersionMinor = deviceSummary.FirmwareVersionMinor;
    memcpy(&_ipAddress, &deviceSummary.IPaddress, 4);
    _hardwareType = deviceSummary.HWtype;
    _dhcp = deviceSummary.DHCP;

    loadPinConfiguration();
}

/**
 *   @brief  Default  destructor for PokeyDevice
 *
 *   @return nothing
 */
PokeyDevice::~PokeyDevice()
{
    PK_DisconnectDevice(_pokey);
}

std::string PokeyDevice::hardwareTypeString()
{
    if (_hardwareType == 31) {
        return "Pokey 57E";
    }
    return "Unknown";
}

bool PokeyDevice::validatePinCapability(int number, std::string type)
{
    // assert(_pokey);
    bool retVal = true;

    return retVal;
}

uint32_t PokeyDevice::targetValue(std::string targetName, bool value)
{
    uint8_t pin = pinFromName(targetName) - 1;
    uint32_t retValue = PK_DigitalIOSetSingle(_pokey, pin, (uint8_t)value);

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

uint32_t PokeyDevice::outputPin(uint8_t pin)
{
    _pokey->Pins[--pin].PinFunction = PK_PinCap_digitalOutput;
    return PK_PinConfigurationSet(_pokey);
}

uint32_t PokeyDevice::inputPin(uint8_t pin)
{
    _pokey->Pins[--pin].PinFunction = PK_PinCap_digitalInput;
    return PK_PinConfigurationSet(_pokey);
}

int32_t PokeyDevice::name(std::string name)
{
    char *temp = (char *)std::calloc(1, 30);
    std::memcpy(_pokey->DeviceData.DeviceName, name.c_str(), 30);
    return PK_DeviceNameSet(_pokey);
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
