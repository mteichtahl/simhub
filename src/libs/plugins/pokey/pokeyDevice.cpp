
#include "pokeyDevice.h"

PokeyDevice::PokeyDevice(sPoKeysNetworkDeviceSummary *deviceSummary, uint8_t index, LoggingFunctionCB _logger)
{
    _index = index;
    _userId = deviceSummary->UserID;
    _serialNumber = deviceSummary->SerialNumber;
    _firwareVersionMajor = deviceSummary->FirmwareVersionMajor;
    _firwareVersionMinor = deviceSummary->FirmwareVersionMinor;
    memcpy(_ipAddress, deviceSummary->IPaddress, 4);
    _hardwareType = deviceSummary->HWtype;
    _dhcp = deviceSummary->DHCP;

    logger = _logger;
}

/**
 *   @brief  Default  destructor for PokeyDevice
 *
 *   @return nothing
 */
PokeyDevice::~PokeyDevice()
{
    logger.log(LOG_INFO, "Closing pokey device %s", _serialNumber);
}