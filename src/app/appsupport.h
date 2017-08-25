#ifndef __INC_APPSUPPORT_H
#define __INC_APPSUPPORT_H

#include <assert.h>
#include <map>
#include <thread>
#include <atomic>
#include <iostream>

/**
 * This class implements the semantic rituals of managing a thread
 * that includes a "cancel" lifecycle
 */
class CancellableThreadManager
{
protected:
    std::shared_ptr<std::thread> _managedThread;
    std::atomic<bool> _threadCancelled;
    std::atomic<bool> _threadRunning;
    
public:
    CancellableThreadManager (void) : _threadCancelled(false), _threadRunning(false) {};
    virtual void shutdownThread(void) 
    { 
        assert(_threadRunning); 
        _threadCancelled = true; 
        do { 
	        // noop
        } while (_threadRunning);
        _managedThread->join();
    };

    std::atomic<bool> &threadCancelled(void) { return _threadCancelled; };
    std::atomic<bool> &threadRunning(void) { return _threadRunning; };
    virtual void setThreadRunning(bool threadRunning) { _threadRunning = threadRunning; };
    virtual void setManagedThread(std::shared_ptr<std::thread> managedThread) { _managedThread = managedThread; };
};

template <typename T, typename E> bool mapContains(const std::map<T, E> &mapInstance, T key)
{
    return mapInstance.find(key) != mapInstance.end();
}

#endif
