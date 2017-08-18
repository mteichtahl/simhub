//
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef CONCURRENT_QUEUE_
#define CONCURRENT_QUEUE_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

class ConcurrentQueueInterrupted : std::exception
{
};

template <typename T> class ConcurrentQueue
{
public:
    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (!terminated_ && queue_.empty()) {
            cond_.wait(mlock);
        }
        if (terminated_) {
            throw ConcurrentQueueInterrupted();
        }
        auto val = queue_.front();
        queue_.pop();
        return val;
    }

    //! provide way to interrupt the blocking cond wait in "pop" member(s)
    void unblock(void)
    {
        terminated_ = true;
        cond_.notify_one();
    }

    void pop(T &item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (!terminated_ && queue_.empty()) {
            cond_.wait(mlock);
        }
        if (terminated_) {
            throw ConcurrentQueueInterrupted();
        }
        item = queue_.front();
        queue_.pop();
    }

    void push(const T &item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }

    ConcurrentQueue()
        : terminated_(false){};
    ConcurrentQueue(const ConcurrentQueue &) = delete; // disable copying
    ConcurrentQueue &operator=(const ConcurrentQueue &) = delete; // disable assignment

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> terminated_;
};

#endif
