#include <iostream>
#include <assert.h>

#include "simsource.h"

class PluginStateManager
{
protected:
	 EnqueueEventHandler _enqueueCallback;

public:
	 PluginStateManager(void);
	 virtual ~PluginStateManager(void);

	 virtual void commenceEventing(EnqueueEventHandler enqueueCallback);
	 virtual void ceaseEventing(void);
};

PluginStateManager::PluginStateManager(void) : _enqueueCallback(NULL)
{
	 std::cout << "simplugin init'd" << std::endl;
}

PluginStateManager::~PluginStateManager(void)
{
	 std::cout << "simplugin release" << std::endl;
}

void PluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback)
{
	 std::cout << "commence eventing" << std::endl;
	 _enqueueCallback = enqueueCallback;
	 enqueueCallback(NULL);
}

void PluginStateManager::ceaseEventing(void)
{
	 std::cout << "cease eventing" << std::endl;

	 _enqueueCallback(NULL);
}
 
// -- public C FFI

extern "C" {

	 int simplug_init(SPHANDLE *plugin_instance)
	 {
		  *plugin_instance = new PluginStateManager();
	 }

	 void simplug_commence_eventing(SPHANDLE plugin_instance, EnqueueEventHandler enqueue_callback)
	 {
		  static_cast<PluginStateManager*>(plugin_instance)->commenceEventing(enqueue_callback);
	 }

	 void simplug_cease_eventing(SPHANDLE plugin_instance)
	 {
		  static_cast<PluginStateManager*>(plugin_instance)->ceaseEventing();
	 }

	 void simplug_release(SPHANDLE plugin_instance)
	 {
		  assert(plugin_instance);
		  delete static_cast<PluginStateManager*>(plugin_instance);
	 }
}

