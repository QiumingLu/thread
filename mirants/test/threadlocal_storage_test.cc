#include "port/threadlocal_storage.h"

#include <string>
#include <stdio.h>
#include "port/current_thread.h"
#include "port/thread.h"

namespace mirants {

class ThreadLocalStorageTest {
 public:
  ThreadLocalStorageTest() {
    printf("tid=%d, constructing %p\n", mirants::currentthread::Tid(), this);
  }

  ~ThreadLocalStorageTest() {
    printf("tid=%d, destructing %p %s\n", mirants::currentthread::Tid(), this, name_.c_str());
  }

  std::string name() const { return name_; }
  void set_name(const std::string& name) { name_ = name; }

 private:
  std::string name_;  
};

ThreadLocalStorage<ThreadLocalStorageTest> obj1;
ThreadLocalStorage<ThreadLocalStorageTest> obj2;

void Test() {
  printf("tid=%d, obj1 %p name=%s\n",
         mirants::currentthread::Tid(),
         *obj1.Get(),
         obj1.Get()->name().c_str());
  printf("tid=%d, obj2 %p name=%s\n",
         mirants::currentthread::Tid(),
         *obj2.Get(),
         obj2.Get()->name().c_str());
}

void ThreadFunc() {
  Test();
  obj1.Get()->set_name("threadfunc one");
  obj2.Get()->set_name("threadfunc two");
  Test();
}

}  // namespace mirants

int main(int argc, char** argv) {
  mirants::obj1.Get()->set_name("main one");
  mirants::Test();
  mirants::Thread t1(mirants::ThreadFunc);
  t1.Start();
  t1.Join();
  mirants::obj2.Get()->set_name("main two");
  mirants::Test();
  pthread_exit(0);
  return 0;
}
