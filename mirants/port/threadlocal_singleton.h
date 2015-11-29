#ifndef THREADLOCAL_SINGLETON_H
#define THREADLOCAL_SINGLETON_H

#include <assert.h>

#include <pthread.h>

#include "noncopyable.h"

template<typename T>
class ThreadLocalSingleton : private Noncopyable {
 public:
  static T& Instance() {
    if (!t_value_) {
      t_value_ = new T();
      deleter_.set(t_value_);
    }
    return *t_value_;
  }

  static T* pointer() {
    return t_value_;
  }

 private:
  ThreadLocalSingleton();
  ~ThreadLocalSingleton();

  static void destructor(void* obj) {
    assert(obj == t_value_);
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
    delete t_value_;
    t_value_ = 0;
  }

  class Deleter {
   public:
    Deleter() {
      pthread_key_create(&pkey_, &ThreadLocalSingleton::destructor);
    }

    ~Deleter() {
      pthread_key_delete(pkey_);
    }

    void set(T* new_obj) {
      assert(pthread_getspecific(pkey_) == NULL);
      pthread_setspecific(pkey_, new_obj);
    }

    pthread_key_t pkey_;
  };

  

  static __thread T* t_value_;
  static Deleter deleter_;
};

template<typename T>
__thread T* ThreadLocalSingleton<T>::t_value_ = NULL;

template<typename T>
typename ThreadLocalSingleton<T>::Deleter ThreadLocalSingleton<T>::deleter_;

#endif  // THREADLOCAL_SINGLETON_H
