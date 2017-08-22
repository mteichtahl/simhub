#ifndef __INC_APPSUPPORT_H
#define __INC_APPSUPPORT_H

#include <assert.h>
#include <map>
#include <thread>
#include <atomic>
#include <iostream>

class CancellableThread
{
protected:
    std::shared_ptr<std::thread> _thread;
    std::atomic<bool> _threadCancelled;
    std::atomic<bool> _threadRunning;
    
public:
    CancellableThread (void) : _threadCancelled(false), _threadRunning(false) {};
    virtual void shutdown(void) 
    { 
        assert(_threadRunning); 
        _threadCancelled = true; 
        do { 
	  // noop
        } while (_threadRunning);
        _thread->join();
    };
};

template <typename T, typename E> bool mapContains(std::map<T, E> &mapInstance, T key)
{
    return mapInstance.find(key) != mapInstance.end();
}

#endif
