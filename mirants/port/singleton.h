#ifndef SINGLETON_H
#define SINGLETON_H

#include "noncopyable.h"

// 单线程下，正确。
// C++11以及以后的版本的多线程下，正确。
// C++11之前的多线程下，不一定正确
// g++ 4.0 后正确

template<typename T> 
class Singleton : private Noncopyable {
 public:
   static T& Instance() {
     static T value;
     return value;
   }

 private:
   Singleton();
   ~Singleton();
};

#endif  // SINGLETON_H
