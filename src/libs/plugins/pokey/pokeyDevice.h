#ifndef __POKEYDEVICE_H
#define __POKEYDEVICE_H

#include "PoKeysLib.h"
#include "common/simhubdeviceplugin.h"
#include <assert.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <uv.h>

#define DEVICE_READ_INTERVAL 100
#define DEVICE_START_DELAY 100
#define ENCODER_1 1
#define ENCODER_2 2
#define ENCODER_3 3
#define DEFAULT_ENCODER_NAME ""
#define DEFAULT_ENCODER_DESCRIPTION ""
#define DEFAULT_ENCODER_MIN 0
#define DEFAULT_ENCODER_MAX 60000
#define DEFAULT_ENCODER_STEP 1
#define DEFAULT_ENCODER_DIRECTION 0

typedef struct {
    std::string pinName;
    int pinNumber;
    std::string type;
    std::string description;
    uint8_t defaultValue;
    uint8_t value;
    uint8_t previousValue;
} device_port_t;

typedef struct {
    std::string name;
    int number;
    std::string description;
    int32_t defaultValue;
    int32_t value;
    int32_t previousValue;
    int32_t previousEncoderValue;
    int32_t min;
    int32_t max;
    int32_t step;
} device_encoder_t;

#define MAX_PINS 55
#define MAX_ENCODERS 10

class PokeyDevice
{
private:
    static void DigitalIOTimerCallback(uv_timer_t *timer, int status);

protected:
    uint8_t _index;
    std::string _serialNumber;
    std::string _description;
    uint8_t _userId;
    uint8_t _firwareVersionMajorMajor;
    uint8_t _firwareVersionMajor;
    uint8_t _firwareVersionMinor;
    uint8_t _ipAddress[4];
    uint8_t _hardwareType;
    uint8_t _dhcp;

    std::map<std::string, int> _pinMap;
    std::map<std::string, int> _encoderMap;

    sPoKeysDevice *_pokey;
    void *_callbackArg;
    SPHANDLE _pluginInstance;
    device_port_t _pins[MAX_PINS];
    device_encoder_t _encoders[MAX_ENCODERS];
    EnqueueEventHandler _enqueueCallback;

    std::shared_ptr<std::thread> _pollThread;
    uv_loop_t *_pollLoop;
    uv_timer_t _pollTimer;

    int pinFromName(std::string targetName);
    void pollCallback(uv_timer_t *timer, int status);

public:
    PokeyDevice(sPoKeysNetworkDeviceSummary, uint8_t);
    virtual ~PokeyDevice(void);

    bool validatePinCapability(int, std::string);
    bool validateEncoder(int encoderNumber);
    void mapNameToPin(std::string name, int pin);
    void mapNameToEncoder(std::string name, int encoderNumber);
    uint32_t targetValue(std::string targetName, bool value);
    uint32_t inputPin(uint8_t pin);
    uint32_t outputPin(uint8_t pin);
    int32_t name(std::string name);

    void setCallbackInfo(EnqueueEventHandler enqueueCallback, void *callbackArg, SPHANDLE pluginInstance);

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
    device_port_t *pins(void) { return _pins; };
    device_encoder_t *encoders() { return _encoders; };
    sPoKeysDevice *pokey() { return _pokey; }
    sPoKeysDevice_Info info() { return _pokey->info; }
    uint8_t numberOfPins() { return info().iPinCount; }
    std::string description() { return _description; }
    sPoKeysDevice_Data deviceData()
    {
        assert(_pokey);
        return _pokey->DeviceData;
    }

    uint8_t loadPinConfiguration() { return PK_PinConfigurationGet(_pokey); }
    bool isPinDigitalOutput(uint8_t pin);
    bool isPinDigitalInput(uint8_t pin);
    bool isEncoderCapable(int pin);
    void addPin(std::string name, int pinNumber, std::string pinType, int defaultValue = 0, std::string description = "None");
    void addEncoder(int encoderNumber, uint32_t defaultValue, std::string name = DEFAULT_ENCODER_NAME, std::string description = DEFAULT_ENCODER_DESCRIPTION,
        int min = DEFAULT_ENCODER_MIN, int max = DEFAULT_ENCODER_MAX, int step = DEFAULT_ENCODER_STEP, int invertDirection = DEFAULT_ENCODER_DIRECTION);

    void startPolling();
    void stopPolling();
    std::string name()
    {
        std::string tmp((char *)deviceData().DeviceName);
        return tmp;
    }
};

#endif
