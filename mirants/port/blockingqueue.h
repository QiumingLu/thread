#ifndef MIRANTS_PORT_BLOCKINGQUEUE_H_
#define MIRANTS_PORT_BLOCKINGQUEUE_H_

#include <deque>
#include <assert.h>
#include <pthread.h>
#include "port/mutex.h"
#include "port/mutexlock.h"

namespace mirants {

template<typename T>
class BlockingQueue {
 public:
  BlockingQueue() : mutex_(), not_empty_(&mutex_) { }

  void Push(const T& t) {
    MutexLock l(&mutex_);
    queue_.push_back(t);
    assert(queue_.size() > 0);
    not_empty_.Signal();
  }

  void Pop() {
    MutexLock l(&mutex_);
    while (queue_.empty()) {
      not_empty_.Wait();
    }
    assert(!queue_.empty());
    queue_.pop_front();
  }

  T Take() {
    MutexLock l(&mutex_);
    while (queue_.empty()) {
      not_empty_.Wait();
    }
    assert(!queue_.empty());
    T t(queue_.front());
    queue_.pop_front();
    return t;
  }

  size_t Size() const {
    MutexLock l(&mutex_);
    return queue_.size();
  }

 private:
  mutable port::Mutex mutex_;
  port::CondVar not_empty_;
  std::deque<T> queue_;

  // No copying allow
  BlockingQueue(const BlockingQueue&);
  void operator=(const BlockingQueue&);
};

}  // namespace mirants 

#endif  // MIRANTS_PORT_BLOCKINGQUEUE_H_
