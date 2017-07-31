#ifndef __INC_POKEYSOURCE_MAIN_H
#define __INC_POKEYSOURCE_MAIN_H

#include <assert.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "PoKeysLib.h"
#include "common/private/pluginstatemanager.h"
#include "common/simhubdeviceplugin.h"
#include "pokeyDevice.h"

#define PREFLIGHT_OK 0
#define PREFLIGHT_FAIL 1

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{

private:
    sPoKeysNetworkDeviceSummary *_networkDeviceSummary;
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;

    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    std::thread *_pluginThread;

protected:
    int _numberOfDevices;
    void discoverDevices();

public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger);
    virtual ~PokeyDevicePluginStateManager(void);
    int preflightComplete(void);
    virtual int deliverValue(genericTLV *value);
};

#endif
