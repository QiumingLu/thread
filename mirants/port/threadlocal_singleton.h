#ifndef MIRANTS_PORT_THREADLOCAL_SINGLETON_H_
#define MIRANTS_PORT_THREADLOCAL_SINGLETON_H_

#include <assert.h>
#include <pthread.h>
#include "noncopyable.h"

namespace mirants {
  
template<typename T>
class ThreadLocalSingleton : private Noncopyable {
 public:
  static T& get() {
    if (!value_) {
      value_ = new T();
      helper_.set(value_);
    }
    return *value_;
  }

  static T* pointer() {
    return value_;
  }

 private:
  ThreadLocalSingleton();
  ~ThreadLocalSingleton();

  static void Delete(void* value) {
    delete static_cast<T*>(value);
  }

  class Helper {
   public:
    Helper() {
      pthread_key_create(&key_, &ThreadLocalSingleton::Delete);
    }

    ~Helper() {
      pthread_key_delete(key_);
    }

    void set(T* value) {
      assert(pthread_getspecific(key_) == NULL);
      pthread_setspecific(key_, value);
    }

    pthread_key_t key_;
  };

  static __thread T* value_;
  static Helper helper_;
};

template<typename T>
__thread T* ThreadLocalSingleton<T>::value_ = NULL;

template<typename T>
typename ThreadLocalSingleton<T>::Helper ThreadLocalSingleton<T>::helper_;

}  // namespace mirants

#endif  // MIRANTS_PORT_THREADLOCAL_SINGLETON_H_
