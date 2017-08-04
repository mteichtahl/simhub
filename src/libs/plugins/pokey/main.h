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

typedef std::shared_ptr<PokeyDevice> pokeyDeviceSharedPointer; ///< shared pointer to a pokey device
typedef std::map<std::string, pokeyDeviceSharedPointer> pokeyDeviceList; ///< a list of unique device pointers
typedef std::pair<pokeyDeviceList::iterator, bool> deviceTargetIterator; ///< iterator for deviceTargers

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
private:
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;
    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    std::map<std::string, pokeyDeviceSharedPointer> _deviceTargetList;

protected:
    bool validateConfig(libconfig::SettingIterator);
    bool getDeviceConfiguration(libconfig::SettingIterator iter, pokeyDeviceSharedPointer pokeyDevice);
    bool getDevicePinsConfiguration(libconfig::Setting *pins, pokeyDeviceSharedPointer pokeyDevice);

    deviceTargetIterator addTargetToDeviceTargetList(std::string, pokeyDeviceSharedPointer);

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
    pokeyDeviceSharedPointer device(std::string);
};

#endif
