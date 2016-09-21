#include "mythread/blockingqueue.h"
#include "mythread/countdownlatch.h"
#include "mythread/thread.h"
#include <string>
#include <stdio.h>

namespace mythread {

class BlockingQueueTest {
 public:
  BlockingQueueTest(int thread_size)
       : thread_size_(thread_size),
         latch_(thread_size) {
  }

  void Start() {
    for (int i = 0; i < thread_size_; ++i) {
      threads_.push_back(new Thread(&BlockingQueueTest::ThreadFunc, this));
    }

    for (size_t i = 0; i < threads_.size(); ++i) {
       threads_[i]->Start();
    }
  }

  void Task(int num) {
    printf("waiting for count down latch\n");
    latch_.Wait();
    for (int i = 1; i <= num; ++i) {
      char task[32];
      snprintf(task, sizeof(task), "task %d", i);
      queue_.push(task);
    }
  }

  void Join() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      queue_.push("No task, stop!");
    }
    for (size_t i = 0; i < threads_.size(); ++i) {
      threads_[i]->Join();
      delete threads_[i];
    }
  }

  void RunFunc() {
    latch_.CountDown();
    while (true) {
      std::string task(queue_.take());
      if (task == "No task, stop!") {
        printf("All taskes have been done! yelp!\n");
        break;
      }
    }
  }

  static void ThreadFunc(void* obj) {
    BlockingQueueTest* t = reinterpret_cast<BlockingQueueTest*>(obj);
    printf("All taskes have been done! yelp!\n");
    t->RunFunc();
  }

 private:
  int thread_size_;
  BlockingQueue<std::string> queue_;
  CountDownLatch latch_;
  std::vector<Thread*> threads_;
};


}  // namespace mythread

int main(int argc, char** argv) {
  mythread::BlockingQueueTest t(5);
  t.Start();
  t.Task(100);
  t.Join();
  return 0;
}
