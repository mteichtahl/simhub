#ifndef __INC_POKEYSOURCE_MAIN_H
#define __INC_POKEYSOURCE_MAIN_H

#include <assert.h>
#include <iostream>
#include <iterator>
#include <thread>
#include <unistd.h>

#include "PoKeysLib.h"
#include "common/private/pluginstatemanager.h"
#include "common/simhubdeviceplugin.h"
#include "pokeyDevice.h"

#define PREFLIGHT_OK 0
#define PREFLIGHT_FAIL 1

// -- pin constants

#define PIN_FREE 0
#define PIN_EXISTS 1

#define PIN_INVALID 0
#define PIN_VALID 1

#define NO_PINS 1

#define UKNOWN_PIN_TYPE 0
#define DIGITAL_INPUT 1
#define DIGITAL_OUTPUT 2
#define ANALOG_INPUT 3
#define ANALOG_OUTPUT 4
#define ENCODER 5
#define FAST_ENCODER 6
#define UFAST_ENCODER 7
#define PWM_INPUT 8
#define COUNTER 9
#define TRIGGER 10

typedef std::pair<std::string, PokeyDevice *> pokeyDevicePair;
typedef std::map<std::string, PokeyDevice *> PokeyDeviceMap; ///< a list of unique device pointers
typedef PokeyDeviceMap::iterator deviceTargetIterator; ///< iterator for deviceTargers

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
private:
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;
    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    static void DigitalIOTimerCallback(uv_timer_t *timer, int status);

    PokeyDeviceMap _deviceTargetList;

protected:
    bool validateConfig(libconfig::SettingIterator);
    bool getDeviceConfiguration(libconfig::SettingIterator iter, PokeyDevice *pokeyDevice);
    bool getDevicePinsConfiguration(libconfig::Setting *pins, PokeyDevice *pokeyDevice);

    bool addTargetToDeviceTargetList(std::string, PokeyDevice *device);
    bool targetFromDeviceTargetList(std::string, PokeyDevice *&ret);
    int startDeviceLoop(void);

    std::shared_ptr<std::thread> _uvPollingThread;
    int _numberOfDevices;
    void enumerateDevices(void);
    PokeyDeviceMap _deviceMap;
    sPoKeysNetworkDeviceSummary *_devices;
    uv_timer_t _uvPollingTimer;
    uv_loop_t* _uvPollingLoop;

public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger);
    virtual ~PokeyDevicePluginStateManager(void);
    int preflightComplete(void);
    virtual int deliverValue(GenericTLV *value);
    virtual void ceaseEventing(void);
    PokeyDevice *device(std::string);
};

#endif
