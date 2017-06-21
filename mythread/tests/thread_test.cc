// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mythread/thread.h"
#include <stdio.h>

namespace mythread {

void ThreadFunc(void*) { printf("hello word!\n"); }

class Foo {
 public:
  static void MemberFunc(void* obj) { printf("%p\n", obj); }
};

void ThreadTest() {
  Thread t1(&ThreadFunc, NULL);
  t1.Start();
  t1.Join();
  Thread t2(&Foo::MemberFunc, &t1);
  t2.Start();
  t2.Join();
}

}  // namespace mythread

int main() {
  mythread::ThreadTest();
  return 0;
}
