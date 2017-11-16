#ifndef __POKEYDEVICE_H
#define __POKEYDEVICE_H

#include "PoKeysLib.h"
#include "common/simhubdeviceplugin.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <uv.h>

#define DEVICE_READ_INTERVAL 100
#define DEVICE_START_DELAY 1000
#define ENCODER_1 1
#define ENCODER_2 2
#define ENCODER_3 3
#define DEFAULT_ENCODER_NAME ""
#define DEFAULT_ENCODER_DESCRIPTION ""
#define DEFAULT_ENCODER_MIN 0
#define DEFAULT_ENCODER_MAX 60000
#define DEFAULT_ENCODER_STEP 1
#define DEFAULT_ENCODER_DIRECTION 0
#define MAX_PINS 55
#define MAX_ENCODERS 10
#define MAX_MATRIX_LEDS 2
#define MAX_MATRIX_LED_GROUPS 8
#define MAX_DIGITS 10
#define MAX_PWM_CHANNELS 6

typedef struct {
    std::string pinName;
    int pinNumber;
    int pinIndex;
    std::string type;
    std::string description;
    std::string units;
    uint8_t defaultValue;
    uint8_t value;
    uint8_t previousValue;
    bool skipNext;
} device_port_t;

typedef struct {
    std::string name;
    int number;
    std::string description;
    std::string units;
    int32_t defaultValue;
    int32_t value;
    int32_t previousValue;
    int32_t previousEncoderValue;
    int32_t min;
    int32_t max;
    int32_t step;
} device_encoder_t;

typedef struct {
    uint8_t position;
    std::string name;
    uint8_t length;
    uint8_t value;
} device_matrixLED_group_t;

typedef struct {
    uint8_t id;
    std::string type;
    std::string name;
    device_matrixLED_group_t group[MAX_MATRIX_LED_GROUPS];
} device_matrixLED_t;

typedef struct {
    uint8_t id;
    std::string name;
    std::string description;
    uint32_t period;
    uint32_t duty;
} device_pwm_t;

class PokeyDevicePluginStateManager;

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
    std::map<std::string, int> _displayMap;
    std::map<std::string, int> _pwmMap;

    PokeyDevicePluginStateManager *_owner;

    sPoKeysDevice *_pokey;
    void *_callbackArg;
    SPHANDLE _pluginInstance;
    device_port_t _pins[MAX_PINS];
    device_pwm_t _pwm[MAX_PWM_CHANNELS];
    device_encoder_t _encoders[MAX_ENCODERS];
    device_matrixLED_t _matrixLED[MAX_MATRIX_LEDS];
    uint8_t _intToDisplayRow[MAX_DIGITS];
    EnqueueEventHandler _enqueueCallback;

    std::shared_ptr<std::thread> _pollThread;
    uv_loop_t *_pollLoop;
    uv_timer_t _pollTimer;

    int pinFromName(std::string targetName);
    int pinIndexFromName(std::string targetName);
    uint8_t displayFromName(std::string targetName);
    uint8_t displayNumber(uint8_t displayNumwber, std::string targetName, int value);

    void pollCallback(uv_timer_t *timer, int status);

public:
    PokeyDevice(PokeyDevicePluginStateManager *owner, sPoKeysNetworkDeviceSummary, uint8_t);
    virtual ~PokeyDevice(void);

    bool ownsPin(std::string pinName);
    bool validatePinCapability(int, std::string);
    bool validateEncoder(int encoderNumber);
    void mapNameToPin(std::string name, int pin);
    void mapNameToEncoder(std::string name, int encoderNumber);
    void mapNameToMatrixLED(std::string name, int id);

    uint32_t targetValue(std::string targetName, bool value);
    uint32_t targetValue(std::string targetName, int value);
    uint32_t inputPin(uint8_t pin, bool invert = false);
    uint32_t outputPin(uint8_t pin);
    int32_t name(std::string name);

    void setCallbackInfo(EnqueueEventHandler enqueueCallback, void *callbackArg, SPHANDLE pluginInstance);

    std::string serialNumber() { return _serialNumber; };
    void setSerialNumber(std::string serialNumber) { _serialNumber = serialNumber; };
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
    sPoKeysMatrixLED *matrixLED() { return _pokey->MatrixLED; };

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
    void addPin(int pindex, std::string name, int pinNumber, std::string pinType, int defaultValue, std::string description, bool invert);
    void addEncoder(int encoderNumber, uint32_t defaultValue, std::string name = DEFAULT_ENCODER_NAME, std::string description = DEFAULT_ENCODER_DESCRIPTION,
        int min = DEFAULT_ENCODER_MIN, int max = DEFAULT_ENCODER_MAX, int step = DEFAULT_ENCODER_STEP, int invertDirection = DEFAULT_ENCODER_DIRECTION, std::string units = "");

    void addMatrixLED(int id, std::string name, std::string type);
    void configMatrixLED(int id, int rows, int cols = 8, int enabled = 0);
    void addGroupToMatrixLED(int id, int displayId, std::string name, int digits, int position);
    void startPolling();
    void stopPolling();
    std::string name();
};

#endif
