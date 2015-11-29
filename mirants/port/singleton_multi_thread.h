#ifndef SINGLETON_MULTI_THREAD_H
#define SINGLETON_MULTI_THREAD_H

#include <assert.h>
#include <stdlib.h>

#include <pthread.h>

#include "noncopyable.h"

template<typename T>
struct has_no_destroy {
  template <typename C> static char test(typeof(&C::nodestroy)); // or decltype in C++11
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};

template<typename T>
class Singleton : private Noncopyable {
 public:
  static T& Instance() {
    pthread_once(&ponce_, &Singleton::init);
    assert(value_ != NULL);
    return *value_;
  }

 private:
  Singleton();
  ~Singleton();

  static void init() {
    value_ = new T();
    if (!has_no_destroy<T>::value) {
      ::atexit(destroy);
    } 
  }

  static void destroy() {
    typedef char T_must_be_complete_type[sizeof(T) == 0? -1 : 1];
    T_must_be_complete_type dumy; (void) dumy;

    delete value_;
    value_ = NULL;
  }

  static pthread_once_t ponce_;
  static T* value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

#endif  // SINGLETON_MULTI_THREAD_H
