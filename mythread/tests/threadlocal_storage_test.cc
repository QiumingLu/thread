// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mythread/threadlocal_storage.h"
#include "mythread/thread.h"
#include <string>
#include <stdio.h>

namespace mythread {

class ThreadLocalStorageTest {
 public:
  std::string name() const { return name_; }
  void set_name(const std::string& name) { name_ = name; }

 private:
  std::string name_;  
};

ThreadLocalStorage<ThreadLocalStorageTest> obj1;
ThreadLocalStorage<ThreadLocalStorageTest> obj2;

void Test() {
  printf("obj1 %p name=%s\n",
         obj1.Get(),
         obj1.Get()->name().c_str());
  printf("obj2 %p name=%s\n",
         obj2.Get(),
         obj2.Get()->name().c_str());
}

void ThreadFunc(void*) {
  Test();
  obj1.Get()->set_name("threadfunc one");
  obj2.Get()->set_name("threadfunc two");
  Test();
}

}  // namespace mythread

int main() {
  mythread::obj1.Get()->set_name("main one");
  mythread::obj2.Get()->set_name("main two");
  mythread::Test();
  mythread::Thread t1(mythread::ThreadFunc, NULL);
  t1.Start();
  t1.Join();
  mythread::Test();
  return 0;
}
