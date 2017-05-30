#ifndef __SIMSOURCE_H
#define __SIMSOURCE_H

#include <dlfcn.h>

#ifdef __cplusplus
extern "C"
{
#endif
#define SPHANDLE void *
    typedef void (*EnqueueEventHandler)(SPHANDLE eventSource, void *event, void *arg);

    typedef enum {
        CONFIG_INT = 0,
        CONFIG_STRING,
        CONFIG_FLOAT
    } ConfigType;

    typedef union {
        float float_value;
        long int_value;
        char *string_value;
    } VariantUnion;

    typedef struct {
        ConfigType type;
        long length;
        VariantUnion value;
    } ConfigEntry;    

    //! basic block of function pointers
    typedef struct {
        //! inits the state manager handle 
        int (*simplug_init)(SPHANDLE *plugin_instance);

        //! pass in named config key/val pair group
        int (*simplug_bind_config_values)(SPHANDLE plugin_instance, char *group_name, ConfigEntry **values, int count);
        //! pre-flight checks method
        int (*simplug_preflight_complete)(SPHANDLE plugin_instance);
        
        /**
         * tell the manager to prepare event loop - the final argment
         * allows the provider of the callback to give a generic
         * handle that has mean within the callback - the same pattern
         * is used in pthread_create
         */
        void (*simplug_commence_eventing)(SPHANDLE plugin_instance,
                                          EnqueueEventHandler event_callback,
                                          void *arg);
        
        //! tell the manager to tear down the event loop
        void (*simplug_cease_eventing)(SPHANDLE plugin_instance);
        
        //! release resources related to the state manager
        void (*simplug_release)(SPHANDLE plugin_instance);
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

        dlerror();    // clear any existing error

        // grab the addresses of the relevant public plugin interface
        // functions
        
        plugin_vtable->simplug_init = (int (*)(SPHANDLE*))dlsym(handle, "simplug_init");
        
        plugin_vtable->simplug_bind_config_values = (int (*)(SPHANDLE, char *, ConfigEntry**, int))dlsym(handle, "simplug_bind_config_values");

        plugin_vtable->simplug_preflight_complete = (int (*)(SPHANDLE))dlsym(handle, "simplug_preflight_complete");

        plugin_vtable->simplug_commence_eventing = (void (*)(SPHANDLE,
                                                             EnqueueEventHandler,
                                                             void *))dlsym(handle, "simplug_commence_eventing");
        
        plugin_vtable->simplug_cease_eventing = (void (*)(SPHANDLE))dlsym(handle, "simplug_cease_eventing");
        
        plugin_vtable->simplug_release = (void (*)(SPHANDLE))dlsym(handle, "simplug_release");

        return 0;
    };

#ifdef __cplusplus
}
#endif

#endif