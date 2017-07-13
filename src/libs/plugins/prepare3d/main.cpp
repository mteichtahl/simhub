#include <assert.h>

#include "common/simhubdeviceplugin.h"
#include "main.h"

// -- public C FFI

extern "C" {
int simplug_init(SPHANDLE *plugin_instance)
{
    *plugin_instance = new SimSourcePluginStateManager();
    return 0;
}

int simplug_bind_config_values(SPHANDLE plugin_instance, char *group_name, ConfigEntry **values, int count)
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
