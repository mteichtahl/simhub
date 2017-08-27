#ifndef __THREADMANAGER_H
#define __THREADMANAGER_H

#include <assert.h>
#include <map>
#include <thread>
#include <atomic>
#include <iostream>

/**
 * This class implements the semantic rituals of managing a thread
 * that includes a "cancel" lifecycle
 */
class CancelableThreadManager
{
protected:
    std::shared_ptr<std::thread> _managedThread;
    std::atomic<bool> _threadCanceled;
    std::atomic<bool> _threadRunning;
    
public:
    CancelableThreadManager (void) : _threadCanceled(false), _threadRunning(false) {};
    virtual void shutdownThread(void) 
    { 
        assert(_threadRunning); 
        _threadCanceled = true; 
        do { 
	        // noop
        } while (_threadRunning);
        _managedThread->join();
    };

    std::atomic<bool> &threadCanceled(void) { return _threadCanceled; };
    std::atomic<bool> &threadRunning(void) { return _threadRunning; };
    virtual void setThreadRunning(bool threadRunning) { _threadRunning = threadRunning; };
    virtual void setManagedThread(std::shared_ptr<std::thread> managedThread) { _managedThread = managedThread; };
};

#endif
