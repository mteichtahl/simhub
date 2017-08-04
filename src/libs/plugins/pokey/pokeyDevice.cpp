#include <string.h>
#include "pokeyDevice.h"

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