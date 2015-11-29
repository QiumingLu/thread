// int pthread_once(pthread_once_t* once_control, void (*init_routine)(void));
// pthread_once_t once_control = PTHREAD_ONCE_INIT

#ifndef MIRANTS_PORT_SINGLETON_H_
#define MIRANTS_PORT_SINGLETON_H_

#include <pthread.h>

namespace mirants {

template<typename T> 
class Singleton {
 public:
  static T* Instance() {
    pthread_once(&once_, &Singleton<T>::Init);
    return instance_;
  }

  static void ShutDown() {
    delete instance_;
    instance_ = NULL;
  }

 private:
  static void Init() {
    instance_ = new T();
  }

  static pthread_once_t once_;
  static T* instance_;
};

template<typename T>
pthread_once_t Singleton<T>::once_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::instance_ = NULL;

}  // namespace mirants

#endif  // MIRANTS_PORT_SINGLETON_H_
