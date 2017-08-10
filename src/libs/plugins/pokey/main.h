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

typedef std::pair<std::string, std::shared_ptr<PokeyDevice>> pokeyDevicePair;
typedef std::map<std::string, std::shared_ptr<PokeyDevice>> PokeyDeviceMap; ///< a list of unique device pointers
typedef PokeyDeviceMap::iterator deviceTargetIterator; ///< iterator for deviceTargers

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
private:
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;
    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    PokeyDeviceMap _deviceTargetList;

protected:
    bool validateConfig(libconfig::SettingIterator);
    bool deviceConfiguration(libconfig::SettingIterator iter, std::shared_ptr<PokeyDevice> &pokeyDevice);
    bool devicePinsConfiguration(libconfig::Setting *pins, std::shared_ptr<PokeyDevice> pokeyDevice);
    bool addTargetToDeviceTargetList(std::string, std::shared_ptr<PokeyDevice> device);
    bool targetFromDeviceTargetList(std::string, std::shared_ptr<PokeyDevice> &ret);
    void enumerateDevices(void);

    std::thread *_pluginThread;
    int _numberOfDevices;
    PokeyDeviceMap _deviceMap;
    sPoKeysNetworkDeviceSummary *_devices;

public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger);
    virtual ~PokeyDevicePluginStateManager(void);
    int preflightComplete(void);
    virtual int deliverValue(GenericTLV *value);
    std::shared_ptr<PokeyDevice> device(std::string);
};

#endif
