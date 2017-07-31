#include "pokeysource_main.h"

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

int simplug_config_passthrough(SPHANDLE plugin_instance, void* libconfig_instance)
{
     return static_cast<PluginStateManager *>(plugin_instance)->configPassthrough(static_cast<libconfig::Setting *>(libconfig_instance));
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

// -- private C++ pokey plugin implementation

int PokeyDevicePluginStateManager::deliverValue(genericTLV *value)
{
    assert(value);
    _logger(LOG_INFO, "Pokey plugin to deliver: %s", value->name);
    return 0;
}

int PokeyDevicePluginStateManager::preflightComplete(void)
{
    // -- at this point we should iterate over our list of libconfig::Setting *'s
    //    and apply the values in  each to the devices we can discover on our network
    //    - fail out appropriately if we can't find all the devices referred to in the
    //      settings list and also if there are more devices discovered than settings
    //      - e.g. dev_missing_config err and config_missing_dev err or something like
    //        that

    _logger(LOG_INFO, "Pokey plugin to discover all connected devices and apply matching elements in _pluginConfigurations to each");

    for (libconfig::Setting *setting: _pluginConfigurations) {
        _logger(LOG_INFO, "got setting for pokey device: %s", setting->lookup("name").c_str());
    }

    return 0;
}