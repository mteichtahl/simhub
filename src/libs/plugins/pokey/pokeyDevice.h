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
    LoggingFunctionCB logger;

protected:
    uint8_t _index;
    std::string _serialNumber;
    uint8_t _userId;
    uint8_t _firwareVersionMajor;
    uint8_t _firwareVersionMinor;
    uint8_t *_ipAddress[4];
    std::string _IPaddressString;
    uint8_t _hardwareType;
    uint8_t _dhcp;

public:
    PokeyDevice(sPoKeysNetworkDeviceSummary *, uint8_t);
    virtual ~PokeyDevice(void);

    inline std::string serialNumber() { return _serialNumber; };
    inline uint8_t userId() { return _userId; };
    inline uint8_t firmwareMajorVersion() { return _firwareVersionMajor; };
    inline uint8_t firmwareMinorVersion() { return _firwareVersionMinor; };
    inline void IPaddressString() { printf("%s.%s.%s.%s", _ipAddress[0], _ipAddress[1], _ipAddress[2], _ipAddress[3]); }
    inline uint8_t hardwareType() { return _hardwareType; }
    inline uint8_t dhcp() { return _dhcp; }
    uint8_t index() { return _index; }
};

#endif