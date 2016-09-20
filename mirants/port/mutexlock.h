#ifndef MIRANTS_UTIL_MUTEXLOCK_H_
#define MIRANTS_UTIL_MUTEXLOCK_H_

#include "port/mutex.h"

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

class MutexLock {
 public:
  explicit MutexLock(port::Mutex* mu)
      : mu_(mu) {
    this->mu_->Lock();
  }
  ~MutexLock() { this->mu_->Unlock(); }

 private:
  port::Mutex* const mu_;
  // No copying allowed
  MutexLock(const MutexLock&);
  void operator=(const MutexLock&);
};

}  // namespace mirants

#endif  //  MIRANTS_UTIL_MUTEXLOCK_H_
