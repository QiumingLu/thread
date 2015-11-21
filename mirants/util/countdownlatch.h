#ifndef MIRANTS_UTIL_COUNTDOWNLATCH_H
#define MIRANTS_UTIL_COUNTDOWNLATCH_H

#include "port/port_posix.h"
#include "util/mutexlock.h"

namespace mirants {

class CountDownLatch {
 public:
  explicit CountDownLatch(int count) 
      : mutex_(),
        condvar_(&mutex_),
        count_(count) {
  }

  void Wait() {
    MutexLock lock(&mutex_);
    while (count_ > 0) {
      condvar_.Wait();
    }
  }

  void CountDown() {
    MutexLock lock(&mutex_);
    --count_;
    if (count_ == 0) {
      condvar_.SignalAll();
    }
  }

  int GetCount() const {
    MutexLock lock(&mutex_);
    return count_;
  }

 private:
  mutable port::Mutex mutex_;
  port::CondVar condvar_;
  int count_;
};

} // namespace mirants

#endif  // MIRANTS_UTIL_COUNTDOWNLATCH_H
