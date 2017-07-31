
#include "pokeyDevice.h"

PokeyDevice::PokeyDevice(sPoKeysNetworkDeviceSummary deviceSummary, uint8_t index)
{

    _pokey = ::PK_ConnectToNetworkDevice(&deviceSummary);
    _index = index;
    _userId = deviceSummary.UserID;
    _serialNumber = deviceSummary.SerialNumber;
    _firwareVersionMajorMajor = (deviceSummary.FirmwareVersionMajor>> 4) + 1;
    _firwareVersionMajor = deviceSummary.FirmwareVersionMajor & 0x0F;
    _firwareVersionMinor = deviceSummary.FirmwareVersionMinor;
     memcpy(&_ipAddress, &deviceSummary.IPaddress, 4);
    _hardwareType = deviceSummary.HWtype;
    _dhcp = deviceSummary.DHCP;
}

/**
 *   @brief  Default  destructor for PokeyDevice
 *
 *   @return nothing
 */
PokeyDevice::~PokeyDevice()
{
    
}

std::string PokeyDevice::hardwareTypeString()
{
    if (_hardwareType == 31){
        return "Pokey 57E";
    }
    return "Unknown";

}