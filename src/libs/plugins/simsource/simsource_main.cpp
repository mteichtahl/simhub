#include <iostream>
#include <thread>
#include <assert.h>
#include <unistd.h>

#include "simsource.h"

class PluginStateManager
{
protected:
	virtual void runTestEventLoop(void);
	EnqueueEventHandler _enqueueCallback;
	std::thread _testEventThread;

public:
	PluginStateManager(void);
	virtual ~PluginStateManager(void);
	
	virtual void commenceEventing(EnqueueEventHandler enqueueCallback);
	virtual void ceaseEventing(void);
};

PluginStateManager::PluginStateManager(void) : _enqueueCallback(NULL)
{
	 std::cout << "simplugin init'd" << std::endl;
	 _testEventThread = std::thread(std::bind(&PluginStateManager::runTestEventLoop, this));
}

PluginStateManager::~PluginStateManager(void)
{
	 std::cout << "simplugin release" << std::endl;
	 _testEventThread.join();
}

void PluginStateManager::runTestEventLoop(void)
{
	std::cout << "generating 9 events in a sleep loop" << std::endl;
	for(size_t i = 0; i < 9; i++) {
		sleep(1);
		_enqueueCallback((void *)"echo");
	}
	std::cout << "done" << std::endl;
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
		  return 0;
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

