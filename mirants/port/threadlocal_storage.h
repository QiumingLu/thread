// Thread-local storage
// int pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
// int pthread_key_delete(pthread_key_t key);
// void* pthread_getspecific(pthread_key_t key);
// int pthread_setspecific(pthread_key_t key, const void* value);
//
#ifndef MIRANTS_PORT_THREADLOCAL_STORAGE_H_
#define MIRANTS_PORT_THREADLOCAL_STORAGE_H_

#include <pthread.h>

namespace mirants {

template<typename T>
class ThreadLocalStorage {
 public:
  ThreadLocalStorage() {
    pthread_key_create(&key_, &ThreadLocalStorage::Delete);
  }
  ~ThreadLocalStorage() {
    pthread_key_delete(key_);
  }

  T* Get() {
    T* result = static_cast<T*>(pthread_getspecific(key_));
    if (result == NULL) {
      result = new T();
      pthread_setspecific(key_, result);
    }
    return result;
  }

 private:
  static void Delete(void* value) {
    delete static_cast<T*>(value);
  }
  pthread_key_t key_;

  // No copying allow
  ThreadLocalStorage(const ThreadLocalStorage&);
  void operator=(const ThreadLocalStorage&);
};

}  // namespace mirants

#endif  // MIRANTS_PORT_THREADLOCAL_STORAGE_H_
