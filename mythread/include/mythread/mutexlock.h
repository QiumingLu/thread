#ifndef MYTHREAD_INCLUDE_MUTEXLOCK_H_
#define MYTHREAD_INCLUDE_MUTEXLOCK_H_

#include "mythread/mutex.h"

namespace mythread {

class MutexLock {
 public:
  explicit MutexLock(Mutex* mutex)
      : mutex_(mutex) {
    mutex_->Lock();
  }

  ~MutexLock() { mutex_->Unlock(); }

 private:
  Mutex* const mutex_;

  // No copying allowed
  MutexLock(const MutexLock&);
  void operator=(const MutexLock&);
};

}  // namespace mythread

#endif  //  MYTHREAD_INCLUDE_MUTEXLOCK_H_
