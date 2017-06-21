// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MYTHREAD_INCLUDE_THREADLOCAL_SINGLETON_H_
#define MYTHREAD_INCLUDE_THREADLOCAL_SINGLETON_H_

#include <assert.h>
#include <pthread.h>

namespace mythread {

template <typename T>
class ThreadLocalSingleton {
 public:
  static T* get() {
    if (!value_) {
      value_ = new T();
      helper_.set(value_);
    }
    return value_;
  }

 private:
  static void Deleter(void* value) { delete reinterpret_cast<T*>(value); }

  class Helper {
   public:
    Helper() { pthread_key_create(&key_, &ThreadLocalSingleton::Deleter); }

    ~Helper() { pthread_key_delete(key_); }

    void set(T* value) {
      assert(pthread_getspecific(key_) == NULL);
      pthread_setspecific(key_, value);
    }

    pthread_key_t key_;
  };

  static __thread T* value_;
  static Helper helper_;
};

template <typename T>
__thread T* ThreadLocalSingleton<T>::value_ = NULL;

template <typename T>
typename ThreadLocalSingleton<T>::Helper ThreadLocalSingleton<T>::helper_;

}  // namespace mythread

#endif  // MYTHREAD_INCLUDE_THREADLOCAL_SINGLETON_H_
