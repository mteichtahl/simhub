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

typedef std::pair<std::string, PokeyDevice *> pokeyDevicePair;
typedef std::map<std::string, PokeyDevice *> pokeyDeviceList; ///< a list of unique device pointers
typedef pokeyDeviceList::iterator deviceTargetIterator; ///< iterator for deviceTargers

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
private:
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;
    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    pokeyDeviceList _deviceTargetList;

protected:
    bool validateConfig(libconfig::SettingIterator);
    bool getDeviceConfiguration(libconfig::SettingIterator iter, PokeyDevice *pokeyDevice);
    bool getDevicePinsConfiguration(libconfig::Setting *pins, PokeyDevice *pokeyDevice);

    bool addTargetToDeviceTargetList(std::string, PokeyDevice *device);
    bool targetFromDeviceTargetList(std::string, PokeyDevice *&ret);

    std::thread *_pluginThread;

    int _numberOfDevices;
    void enumerateDevices(void);
    pokeyDeviceList _deviceList;
    sPoKeysNetworkDeviceSummary *_devices;

public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger);
    virtual ~PokeyDevicePluginStateManager(void);
    int preflightComplete(void);
    virtual int deliverValue(GenericTLV *value);
    PokeyDevice *device(std::string);
};

#endif
