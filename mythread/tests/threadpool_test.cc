#include "mythread/threadpool.h"
#include <stdio.h>
#include "mythread/countdownlatch.h"

namespace mythread {

void Print(void* obj) { printf("%p, hello word!\n", obj); }

void DoCountDown(void* obj) {
  CountDownLatch* latch = reinterpret_cast<CountDownLatch*>(obj);
  latch->CountDown();
}

void Test(int poolsize) {
  ThreadPool pool(poolsize);
  pool.Start();
  for (int i = 0; i < 40; ++i) {
    pool.Put(&Print, &pool);
  }
  CountDownLatch latch(1);
  pool.Put(&DoCountDown, &latch);
  latch.Wait();
  pool.Stop();
}

}  // namespace mythread

int main() {
  mythread::Test(4);
  return 0;
}
