#ifndef __POKEYDEVICE_H
#define __POKEYDEVICE_H

#include "common/simhubdeviceplugin.h"
#include <assert.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "PoKeysLib.h"

class PokeyDevice
{
private:
protected:
    uint8_t _index;
    std::string _serialNumber;
    uint8_t _userId;
    uint8_t _firwareVersionMajorMajor;
    uint8_t _firwareVersionMajor;
    uint8_t _firwareVersionMinor;
    uint8_t _ipAddress[4];
    uint8_t _hardwareType;
    uint8_t _dhcp;
    sPoKeysDevice *_pokey;

public:
    PokeyDevice(sPoKeysNetworkDeviceSummary, uint8_t);
    virtual ~PokeyDevice(void);

    bool validatePinCapability(int, std::string);

    std::string serialNumber() { return _serialNumber; };
    uint8_t userId() { return _userId; };
    uint8_t firmwareMajorMajorVersion() { return _firwareVersionMajorMajor; };
    uint8_t firmwareMajorVersion() { return _firwareVersionMajor; };
    uint8_t firmwareMinorVersion() { return _firwareVersionMinor; };
    uint8_t hardwareType() { return _hardwareType; }
    std::string hardwareTypeString();
    uint8_t dhcp() { return _dhcp; }
    uint8_t index() { return _index; }
    uint8_t *ipAddress() { return _ipAddress; }
    sPoKeysDevice *pokey() { return _pokey; }
    sPoKeysDevice_Info info() { return _pokey->info; }
    sPoKeysDevice_Data deviceData() { return _pokey->DeviceData; }
    uint8_t loadPinConfiguration() { return PK_PinConfigurationGet(_pokey); }
    std::string name()
    {
        std::string tmp((char *)deviceData().DeviceName);
        return tmp;
    }
};

#endif