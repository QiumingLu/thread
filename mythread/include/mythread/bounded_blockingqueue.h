// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
        not_full_(&mutex_),
        not_empty_(&mutex_),
        capacity_(capacity) {
  }

  void push(const T& t) {
    MutexLock lock(&mutex_);
    while (queue_.size() == capacity_) {
      not_full_.Wait();
    }
    assert(queue_.size() < capacity_);
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
    if (queue_.size() == capacity_) {
      not_full_.Signal();
    }
    queue_.pop();
  }

  T take() {
    MutexLock lock(&mutex_);
    while (queue_.empty()) {
      not_empty_.Wait();
    }
    assert(!queue_.empty());
    if (queue_.size() == capacity_) {
      not_full_.Signal();
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
  Condition not_full_;
  Condition not_empty_;
  const size_t capacity_;
  std::queue<T> queue_;

  // No copying allowed
  BoundedBlockingQueue(const BoundedBlockingQueue&);
  void operator=(const BoundedBlockingQueue&);
};

}  // namespace mythread

#endif  // MYTHREAD_INCLUDE_BOUNDED_BLOCKINGQUEUE_H_
