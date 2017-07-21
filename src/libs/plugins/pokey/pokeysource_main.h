#ifndef __INC_POKEYSOURCE_MAIN_H
#define __INC_POKEYSOURCE_MAIN_H

#include <assert.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "common/simhubdeviceplugin.h"
#include "common/private/pluginstatemanager.h"

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger) : PluginStateManager(logger) {};
};

#endif
