#include "include/mythread/bounded_blockingqueue.h"
#include "include/mythread/countdownlatch.h"
#include "include/mythread/thread.h"

#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

#include <memory>
#include <vector>

namespace mythread {

using namespace std::placeholders;

class BoundedBlockingQueueTest {
 public:
  BoundedBlockingQueueTest(int threads_size)
      : queue_(18),
        latch_(threads_size),
        threads_size_(threads_size) {
    for (int i = 0; i < threads_size_; ++i) {
      threads_.push_back(std::unique_ptr<Thread>(new Thread(
            std::bind(&BoundedBlockingQueueTest::ThreadFunc, this),
            StringPrintf("thread %d", i))));
      threads_[i]->Start();
    }
  }

  void Task(int num) {
    printf("waiting for all threads start...\n");
    latch_.Wait();
    for (int i = 1; i <= num; ++i) {
      std::string task(StringPrintf("task %d", i));
      queue_.Put(task);
      printf("tid=%" PRIu64", add task=%s, queue's size=%zd\n",
             CurrentThread::Tid(), task.c_str(), queue_.Size());
    }
  }

  void JoinAll() {
    for (int i = 0; i < threads_size_; ++i) {
      queue_.Put("No task, stop!");
    }
    for (int i = 0; i < threads_size_; ++i) {
      threads_[i]->Join();
    }
  }

 private:
  void ThreadFunc() {
    printf("tid=%" PRIu64", %s started.\n",
           CurrentThread::Tid(), CurrentThread::ThreadName());
    latch_.CountDown();
    while (true) {
      std::string task(queue_.Take());
      if (task == "No task, stop!") {
        printf("All taskes have been done! Yelp!\n");
        printf("tid=%" PRIu64", get task = %s, queue's size = %zd\n",
               CurrentThread::Tid(), task.c_str(), queue_.Size());
        break;
      }
    }
  }

  BoundedBlockingQueue<std::string> queue_;
  CountDownLatch latch_;
  int threads_size_;
  std::vector<std::unique_ptr<Thread>> threads_;
};

}  // namespace mythread

int main(int argc, char** argv) {
  mythread::BoundedBlockingQueueTest t(4);
  t.Task(100);
  t.JoinAll();
  return 0;
}
