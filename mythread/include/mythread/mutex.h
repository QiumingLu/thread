#ifndef MYTHREAD_INCLUDE_MUTEX_H_
#define MYTHREAD_INCLUDE_MUTEX_H_

#include <pthread.h>

namespace mythread {

class Condition;

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();
  void AssertHeld() { }

 private:
  friend class Condition;
  pthread_mutex_t mutex_;

  // No copying allowed
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

class Condition {
 public:
  explicit Condition(Mutex* mutex);
  ~Condition();

  void Wait();
  void Signal();
  void SignalAll();

 private:
  pthread_cond_t cond_;
  Mutex* mutex_;
};

} // namespace mythread

#endif  // MYTHREAD_INCLUDE_MUTEX_H_
