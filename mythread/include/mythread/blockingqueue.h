#ifndef MYTHREAD_INCLUDE_BLOCKINGQUEUE_H_
#define MYTHREAD_INCLUDE_BLOCKINGQUEUE_H_

#include <assert.h>
#include <queue>
#include "mythread/mutexlock.h"

namespace mythread {

template<typename T>
class BlockingQueue {
 public:
  BlockingQueue() : mutex_(), not_empty_(&mutex_) { }

  void push(const T& t) {
    MutexLock lock(&mutex_);
    if (queue_.empty()) {
      not_empty_.Signal();
    }
    queue_.push(t);
  }

  void pop() {
    MutexLock lock(&mutex_);
    while (queue_.empty()) {
      not_empty_.Wait();
    }
    assert(!queue_.empty());
    queue_.pop();
  }

  T take() {
    MutexLock lock(&mutex_);
    while (queue_.empty()) {
      not_empty_.Wait();
    }
    assert(!queue_.empty());
    T t(queue_.front());
    queue_.pop();
    return t;
  }

  bool empty() const {
    MutexLock lock(&mutex_);
    return queue_.empty();
  }

  size_t size() const {
    MutexLock lock(&mutex_);
    return queue_.size();
  }

 private:
  mutable Mutex mutex_;
  Condition not_empty_;
  std::queue<T> queue_;

  // No copying allowed
  BlockingQueue(const BlockingQueue&);
  void operator=(const BlockingQueue&);
};

}  // namespace mirants

#endif  // MIRANTS_PORT_BLOCKINGQUEUE_H_
