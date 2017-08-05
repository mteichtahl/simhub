#ifndef __SIMSOURCE_H
#define __SIMSOURCE_H

#include <dlfcn.h>

#if defined(build_macosx)
#define LIB_EXT ".dylib"
#endif

#if defined(build_linux)
#define LIB_EXT ".so"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SPHANDLE void *

typedef void (*EnqueueEventHandler)(SPHANDLE eventSource, void *event, void *arg);

typedef void (*LoggingFunctionCB)(const int category, const char *msg, ...);

typedef enum { CONFIG_INT = 0, CONFIG_STRING, CONFIG_FLOAT, CONFIG_BOOL } ConfigType;

typedef union {
    float float_value;
    long int_value;
    char *string_value;
    int bool_value;
} VariantUnion;

typedef struct {
    char *name;
    ConfigType type;
    long length;
    VariantUnion value;
} GenericTLV;

//! basic block of function pointers
typedef struct {
    //! inits the state manager handle
    int (*simplug_init)(SPHANDLE *plugin_instance, LoggingFunctionCB logger);

    //! pass through kludge until we split out config files
    int (*simplug_config_passthrough)(SPHANDLE plugin_instance, void *libconfig_instance);

    //! pre-flight checks method
    int (*simplug_preflight_complete)(SPHANDLE plugin_instance);

    /**
     * tell the manager to prepare event loop - the final argment
     * allows the provider of the callback to give a generic
     * handle that has mean within the callback - the same pattern
     * is used in pthread_create
     */
    void (*simplug_commence_eventing)(SPHANDLE plugin_instance, EnqueueEventHandler event_callback, void *arg);

    /**
     * instruct the plugin instance to synchronously deliver a value to the value name
     * - the name is actually a name-spaced endpoint
     */
    int (*simplug_deliver_value)(SPHANDLE plugin_instance, GenericTLV *value);

    //! tell the manager to tear down the event loop
    void (*simplug_cease_eventing)(SPHANDLE plugin_instance);

    //! release resources related to the state manager
    void (*simplug_release)(SPHANDLE plugin_instance);

    //! convenience struct member so that users of this struct can store the instance with its methods
    SPHANDLE plugin_instance;
} simplug_vtable;

/**
 * attempts to load the given shared library and extract a small vtable
 * functions out of it
 */
inline int simplug_bootstrap(const char *plugin_path, simplug_vtable *plugin_vtable)
{
    void *handle = dlopen(plugin_path, RTLD_LAZY);

    if (!handle) {
        return -1;
    }

    dlerror(); // clear any existing error

    // grab the addresses of the relevant public plugin interface
    // functions

    plugin_vtable->simplug_init = (int (*)(SPHANDLE *, LoggingFunctionCB))dlsym(handle, "simplug_init");
    if (!plugin_vtable->simplug_init)
        return -1;

    plugin_vtable->simplug_config_passthrough = (int (*)(SPHANDLE, void *))dlsym(handle, "simplug_config_passthrough");
    if (!plugin_vtable->simplug_config_passthrough)
        return -1;

    plugin_vtable->simplug_preflight_complete = (int (*)(SPHANDLE))dlsym(handle, "simplug_preflight_complete");
    if (!plugin_vtable->simplug_preflight_complete)
        return -1;

    plugin_vtable->simplug_commence_eventing = (void (*)(SPHANDLE, EnqueueEventHandler, void *))dlsym(handle, "simplug_commence_eventing");
    if (!plugin_vtable->simplug_commence_eventing)
        return -1;

    plugin_vtable->simplug_deliver_value = (int (*)(SPHANDLE, GenericTLV *))dlsym(handle, "simplug_deliver_value");
    // NOTE: at this point plugins can optionally implement the deliver_value function

    plugin_vtable->simplug_cease_eventing = (void (*)(SPHANDLE))dlsym(handle, "simplug_cease_eventing");
    if (!plugin_vtable->simplug_cease_eventing)
        return -1;

    plugin_vtable->simplug_release = (void (*)(SPHANDLE))dlsym(handle, "simplug_release");
    if (!plugin_vtable->simplug_release)
        return -1;

    return 0;
};

#ifdef __cplusplus
}
#endif

#endif
