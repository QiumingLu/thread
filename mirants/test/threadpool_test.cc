#include "port/threadpool.h"
#include "port/current_thread.h"
#include "port/countdownlatch.h"

namespace mirants {

void Print() {
  printf("tid=%d\n", currentthread::Tid());
}

void Test(int poolsize) {
  ThreadPool pool(poolsize, "Main ThreadPool");
  pool.Start();
  for (int i = 0; i < 100; ++i) {
    pool.PushTaskInToPool(Print);
  }
  CountDownLatch latch(1);
  pool.PushTaskInToPool(std::bind(&CountDownLatch::CountDown, &latch));
  latch.Wait();
  pool.ShutDown();
}

}  // namespace mirants

int main(int argc, char** argv) {
  mirants::Test(4);
  return 0;
}

