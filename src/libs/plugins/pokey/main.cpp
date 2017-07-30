#include <assert.h>
#include <iostream>
#include <memory>
#include <vector>

#include "common/simhubdeviceplugin.h"
#include "main.h"

// -- public C FFI

extern "C" {

int simplug_init(SPHANDLE *plugin_instance, LoggingFunctionCB logger)
{
    *plugin_instance = new PokeyDevicePluginStateManager(logger);
    return 0;
}

int simplug_bind_config_values(SPHANDLE plugin_instance, char *group_name, genericTLV **values, int count)
{
    return static_cast<PluginStateManager *>(plugin_instance)->bindConfigValues(group_name, values, count);
}

int simplug_preflight_complete(SPHANDLE plugin_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->preflightComplete();
}

void simplug_commence_eventing(SPHANDLE plugin_instance, EnqueueEventHandler enqueue_callback, void *arg)
{
    static_cast<PluginStateManager *>(plugin_instance)->commenceEventing(enqueue_callback, arg);
}

int simplug_deliver_value(SPHANDLE plugin_instance, genericTLV *value)
{
    return static_cast<PluginStateManager *>(plugin_instance)->deliverValue(value);
}

void simplug_cease_eventing(SPHANDLE plugin_instance)
{
    static_cast<PluginStateManager *>(plugin_instance)->ceaseEventing();
}

void simplug_release(SPHANDLE plugin_instance)
{
    assert(plugin_instance);
    delete static_cast<PluginStateManager *>(plugin_instance);
}
}

PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::_StateManagerInstance = NULL;

// -- private C++ pokey plugin implementation

PokeyDevicePluginStateManager::PokeyDevicePluginStateManager(LoggingFunctionCB logger)
    : PluginStateManager(logger)
{
    _numberOfDevices = 0; ///< 0 devices discovered
    _networkDeviceSummary = (sPoKeysNetworkDeviceSummary *)calloc(sizeof(sPoKeysNetworkDeviceSummary), 16); ///<0 initialise the network device summary
}

//! static getter for singleton instance of our class
PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

PokeyDevicePluginStateManager::~PokeyDevicePluginStateManager(void)
{
    // TODO: enable once shtudown implemented
    if (_pluginThread != NULL) {
        if (_pluginThread->joinable()) {
            ceaseEventing();
            _pluginThread->join();
        }
        free(_networkDeviceSummary);
        delete _pluginThread;
    }
}

int PokeyDevicePluginStateManager::deliverValue(genericTLV *value)
{
    assert(value);
    _logger(LOG_INFO, "Pokey plugin to deliver: %s", value->name);
    return 0;
}

void PokeyDevicePluginStateManager::discoverDevices()
{
    _logger(LOG_INFO, " - Discovering Pokey Devices");
    _numberOfDevices = PK_EnumerateNetworkDevices(_networkDeviceSummary, 800);
}

int PokeyDevicePluginStateManager::preflightComplete(void)
{
    int retVal = PREFLIGHT_OK;

    discoverDevices();
    if (_numberOfDevices > 0) {
        _logger(LOG_INFO, "  - discovered %d", _numberOfDevices);
        retVal = PREFLIGHT_OK;
    }
    else {
        _logger(LOG_INFO, "  - No devices discovered");
    }

    return retVal;
}
