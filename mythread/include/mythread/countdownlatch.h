#ifndef MYTHREAD_INCLUDE_COUNTDOWNLATCH_H_
#define MYTHREAD_INCLUDE_COUNTDOWNLATCH_H_

#include "mythread/mutexlock.h"

namespace mythread {

class CountDownLatch {
 public:
  explicit CountDownLatch(int count)
      : mutex_(),
        cond_(&mutex_),
        count_(count) {
  }

  void Wait() {
    MutexLock lock(&mutex_);
    while (count_ > 0) {
      cond_.Wait();
    }
  }

  void CountDown() {
    MutexLock lock(&mutex_);
    --count_;
    if (count_ == 0) {
      cond_.Signal();
    }
  }

  int GetCount() const {
    MutexLock lock(&mutex_);
    return count_;
  }

 private:
  mutable Mutex mutex_;
  Condition cond_;
  int count_;
};

} // namespace mythread

#endif  // MYTHREAD_INCLUDE_COUNTDOWNLATCH_H_
