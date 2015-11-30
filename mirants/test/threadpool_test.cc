#include "port/threadpool.h"
#include "port/current_thread.h"

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
  pool.ShutDown();
}

}  // namespace mirants

int main(int argc, char** argv) {
  mirants::Test(2);
  return 0;
}

