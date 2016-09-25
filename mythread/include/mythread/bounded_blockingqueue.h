#ifndef MYTHREAD_INCLUDE_BOUNDED_BLOCKINGQUEUE_H_
#define MYTHREAD_INCLUDE_BOUNDED_BLOCKINGQUEUE_H_

#include <assert.h>
#include <queue>
#include "mythread/mutexlock.h"

namespace mythread {

template<typename T>
class BoundedBlockingQueue {
 public:
  explicit BoundedBlockingQueue(size_t capacity)
      : mutex_(),
        not_full(&mutex_),
        not_empty(&mutex_),
        capacity_(capacity) {
  }

  void push(const T& t) {
    MutexLock lock(&mutex_);
    while (queue_.size() == capacity_) {
      not_full.Wait();
    }
    assert(queue_.size() < capacity_);
    if (queue_.empty()) {
      not_empty.Signal();
    }
    queue_.push(t);
  }

  void pop() {
    MutexLock lock(&mutex_);
    while (queue_.empty()) {
      not_empty.Wait();
    }
    assert(!queue_.empty());
    if (queue_.size() == capacity_) {
      not_full.Signal();
    }
    queue_.pop();
  }

  T take() {
    MutexLock lock(&mutex_);
    while (queue_.empty()) {
      not_empty.Wait();
    }
    assert(!queue_.empty());
    if (queue_.size() == capacity_) {
      not_full.Signal();
    }
    T t(queue_.front());
    queue_.pop();
    return t;
  }

  size_t capacity() const {
    MutexLock lock(&mutex_);
    return capacity_;
  }

  size_t size() const {
    MutexLock lock(&mutex_);
    return queue_.size();
  }

  bool empty() const {
    MutexLock lock(&mutex_);
    return queue_.empty();
  }

  bool full() const {
    MutexLock lock(&mutex_);
    if (queue_.size() == capacity_) {
      return true;
    }
    return false;
  }

 private:
  mutable Mutex mutex_;
  Condition not_full;
  Condition not_empty;
  const size_t capacity_;
  std::queue<T> queue_;

  // No copying allowed
  BoundedBlockingQueue(const BoundedBlockingQueue&);
  void operator=(const BoundedBlockingQueue&);
};

}  // namespace mythread

#endif  // MYTHREAD_INCLUDE_BOUNDED_BLOCKINGQUEUE_H_
