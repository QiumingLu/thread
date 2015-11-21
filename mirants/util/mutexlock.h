#ifndef MIRANTS_UTIL_MUTEXLOCK_H
#define MIRANTS_UTIL_MUTEXLOCK_H

#include "port/port_posix.h"
#include "port/thread_annotations.h"

namespace mirants {

  // Helper class that locks a mutex on construction and unlocks the mutex 
  // when the destructor of the MutexLock object is invoked.
  //
  // Typical usage:
  //
  //  void MyClass::MyMethod() {
  //  MutexLock l(&mu_);        // mu_ is an instance variable
  //  ... some complex code, possibly with multiple return paths ...
  //  }

class SCOPED_LOCKABLE MutexLock {
 public:
  explicit MutexLock(port::Mutex* mu) EXCLUSIVE_LOCK_FUNCTION(mu) 
      : mu_(mu) {
    this->mu_->Lock();
  }
  ~MutexLock() UNLOCK_FUNCTION() { this->mu_->Unlock(); }

 private:
  port::Mutex* const mu_;
  // No copying allowed
  MutexLock(const MutexLock&);
  void operator=(const MutexLock&);
};

}  // namespace mirants

#endif  //  MIRANTS_UTIL_MUTEXLOCK_H
